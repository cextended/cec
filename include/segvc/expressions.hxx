#pragma once

#include <string>
#include <memory>
#include <vector>

#include <segvc/typer.hxx>

enum class OPE {
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,

	SHL,
	SHR,

	TER, // ternary, x ? 1 : 0

	EQEQ,
	AND,
	OR,
	ANDAND,
	OROR,

	XOR,

	ASSIGN, // =

	ADDR, // &x
	DEREF, // *x

	// Unary Operators
	NOT, // !
	NEG, // ~x
	INCB, // ++x
	INCA, // x++
	DECB, // --x
	DECA, // x--
	TYPECAST, // (typename)x

	COMMA // <Expression>, <Expression>       see: https://en.wikipedia.org/wiki/Comma_operator
};

struct ExpressionVisitor;

struct Expression {
	virtual ~Expression() = default;
	virtual void accept(ExpressionVisitor& v) = 0;
};

using ExprPtr = std::shared_ptr<Expression>;

struct BinaryExpression : public Expression {
	ExprPtr left, right;
	OPE op;

	BinaryExpression(ExprPtr left, OPE op, ExprPtr right);

	void accept(ExpressionVisitor& v) override;
};

struct TupleExpression : public Expression {
	std::vector<ExprPtr> expressions;
	void accept(ExpressionVisitor& v) override;
};

struct UnaryExpression : public Expression {
        ExprPtr te;
        OPE op;
	ExprPtr param;

        UnaryExpression(ExprPtr te, OPE op);

        void accept(ExpressionVisitor& v) override;
};

enum {
	LIT_NUMBER,
	LIT_CHAR,
	LIT_STRING
};

struct LiteralExpression : public Expression {
	int ltype;
	std::string value;

	LiteralExpression(int ltype, std::string value);

        void accept(ExpressionVisitor& v) override;
};

struct VariableExpression : public Expression {
	std::string name;

	VariableExpression(std::string name);

        void accept(ExpressionVisitor& v) override;
};


/**
 *  Using for reaching members with ' . ' or ' -> ' operator
 *  eg.
 *     let foo Foo
 *     foo.bar();
 */
struct MemberExpression : public VariableExpression {
	bool isPointer;
	ExprPtr parent;

	MemberExpression(ExprPtr parent, std::string name);

        void accept(ExpressionVisitor& v) override;
};

/**
 *  Using for reaching elements through array and map
 *  eg.
 *     let mymap hashmap<string, int>
 *     map["foo"] = bar
 */
struct SubscriptExpression : public Expression {
	bool isPointer;
	ExprPtr parent;
	ExprPtr index;

	SubscriptExpression(ExprPtr parent, ExprPtr index);

        void accept(ExpressionVisitor& v) override;
};

struct FunctionCallExpression : public Expression {
	ExprPtr function;
	std::shared_ptr<TupleExpression> params;

	FunctionCallExpression(ExprPtr func, std::shared_ptr<TupleExpression> params);

	void accept(ExpressionVisitor& v) override;
};

struct Statement {
	virtual ~Statement() = default;
	virtual void accept(ExpressionVisitor& v) = 0;
};

using StmPtr = std::shared_ptr<Statement>;

enum DeclarationType {
	UNDEFINED = 0,
	CONST,
	STATIC
};

struct DeclarationStatement : Statement {
	std::string name;
	DeclarationType dec_type;
	std::shared_ptr<Typer> type_spec;
	ExprPtr initializer;

	void accept(ExpressionVisitor& v) override;
};

struct MultipleDeclarationStatement : Statement {
	std::vector< std::shared_ptr<DeclarationStatement> > list;
	ExprPtr initializer;

	void accept(ExpressionVisitor& v) override;
};

struct BlockStatement : public Statement {
	std::vector<StmPtr> childs;

	void accept(ExpressionVisitor& v) override;
};

struct FunctionDeclarationStatement : Statement {
        std::string name;
	DeclarationType dec_type;
        std::shared_ptr<Typer> type_spec;
        std::shared_ptr<BlockStatement> body;

        void accept(ExpressionVisitor& v) override;
};

struct ExpressionStatement : public Statement {
	ExprPtr expr;

	void accept(ExpressionVisitor& v) override;
};

struct IfStatement : public Statement {
	ExprPtr condition;
	StmPtr body;

	void accept(ExpressionVisitor& v) override;
};

struct WhileStatement : public IfStatement {
	ExprPtr condition;

	StmPtr lead, body, trail;

	void accept(ExpressionVisitor& v) override;
};

struct BasicForStatement : public Statement {
	std::shared_ptr<BlockStatement> init;

	StmPtr lead, body, trail;

	virtual void accept(ExpressionVisitor& v) override = 0;
};

struct ForStatement : public BasicForStatement {
	ExprPtr condition;
	StmPtr update;

	void accept(ExpressionVisitor& v) override;
};

struct ForEachStatement : public BasicForStatement {
	ExprPtr iterable;

	void accept(ExpressionVisitor& v) override;
};

struct ReturnStatement : public Statement {
	ExprPtr expr;

	void accept(ExpressionVisitor& v) override;
};

struct ExpressionVisitor {
	virtual void visit(BinaryExpression &e) = 0;
	virtual void visit(TupleExpression &e) = 0;
	virtual void visit(UnaryExpression &e) = 0;
	virtual void visit(LiteralExpression &e) = 0;
	virtual void visit(VariableExpression &e) = 0;
	virtual void visit(MemberExpression &e) = 0;
	virtual void visit(SubscriptExpression &e) = 0;
	virtual void visit(FunctionCallExpression &e) = 0;

	virtual void visit(DeclarationStatement &s) = 0;
	virtual void visit(MultipleDeclarationStatement &s) = 0;
	virtual void visit(BlockStatement &s) = 0;
	virtual void visit(FunctionDeclarationStatement &s) = 0;
	virtual void visit(ExpressionStatement &s) = 0;
	virtual void visit(IfStatement &s) = 0;
	virtual void visit(WhileStatement &s) = 0;
	virtual void visit(ForStatement &s) = 0;
	virtual void visit(ForEachStatement &s) = 0;
	virtual void visit(ReturnStatement &s) = 0;
};
