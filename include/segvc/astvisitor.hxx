#pragma once
#include <segvc/expressions.hxx>
#include <segvc/irvalue.hxx>

struct ExpressionVisitor {

	virtual std::unique_ptr<IRValue> begin() = 0;
	virtual std::unique_ptr<IRValue> end() = 0;

	virtual std::unique_ptr<IRValue> visit(BinaryExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(TupleExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(UnaryExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(LiteralExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(VariableExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(MemberExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(SubscriptExpression &e) = 0;
	virtual std::unique_ptr<IRValue> visit(FunctionCallExpression &e) = 0;
};

struct StatementVisitor {
	virtual void begin() = 0;
	virtual void end() = 0;

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
