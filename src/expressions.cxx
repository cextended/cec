#include <segvc/expressions.hxx>

BinaryExpression::BinaryExpression(ExprPtr left, OPE op, ExprPtr right) : left(left), op(op), right(right) {}
UnaryExpression::UnaryExpression(ExprPtr te, OPE op) : te(te), op(op) {}
LiteralExpression::LiteralExpression(int ltype, std::string value) : ltype(ltype), value(value) {}
VariableExpression::VariableExpression(std::string name) : name(name) {}
MemberExpression::MemberExpression(ExprPtr parent, std::string name) : parent(parent), VariableExpression(name) {}
SubscriptExpression::SubscriptExpression(ExprPtr parent, ExprPtr index) : parent(parent), index(index) {}

void BinaryExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void TupleExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void UnaryExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void LiteralExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void VariableExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void SubscriptExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void MemberExpression::accept(ExpressionVisitor& v) { v.visit(*this); }

void DeclarationStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void MultipleDeclarationStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void BlockStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void FunctionDeclarationStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void ExpressionStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void IfStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void WhileStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void ForStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void ForEachStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
void ReturnStatement::accept(ExpressionVisitor& v) { v.visit(*this); }
