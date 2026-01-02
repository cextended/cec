#pragma once
#include <segvc/expressions.hxx>
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
