#include <segvc/expressionvisitor.hxx>

void BinaryExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void TupleExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void UnaryExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void LiteralExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void VariableExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void SubscriptExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void MemberExpression::accept(ExpressionVisitor& v) { v.visit(*this); }
void FunctionCallExpression::accept(ExpressionVisitor& v) { v.visit(*this); }

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
