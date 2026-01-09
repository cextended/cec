#include <segvc/astvisitor.hxx>
#include <segvc/expressions.hxx>

namespace segvc {

BinaryExpression::BinaryExpression(ExprPtr left, OPE op, ExprPtr right) : left(left), op(op), right(right) {}
UnaryExpression::UnaryExpression(ExprPtr te, OPE op) : te(te), op(op) {}
LiteralExpression::LiteralExpression(int ltype, std::string value) : ltype(ltype), value(value) {}
VariableExpression::VariableExpression(std::string name) : name(name) {}
MemberExpression::MemberExpression(ExprPtr parent, std::string name) : parent(parent), VariableExpression(name) {}
SubscriptExpression::SubscriptExpression(ExprPtr parent, ExprPtr index) : parent(parent), index(index) {}
FunctionCallExpression::FunctionCallExpression(ExprPtr function, std::shared_ptr<TupleExpression> params) : function(function), params(params) {}

std::unique_ptr<IRValue> BinaryExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> TupleExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> UnaryExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> LiteralExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> VariableExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> SubscriptExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> MemberExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }
std::unique_ptr<IRValue> FunctionCallExpression::accept(ExpressionVisitor& v) { return v.visit(*this); }

void DeclarationStatement::accept(StatementVisitor& v) { v.visit(*this); }
void MultipleDeclarationStatement::accept(StatementVisitor& v) { v.visit(*this); }
void BlockStatement::accept(StatementVisitor& v) { v.visit(*this); }
void FunctionDeclarationStatement::accept(StatementVisitor& v) { v.visit(*this); }
void ExpressionStatement::accept(StatementVisitor& v) { v.visit(*this); }
void IfStatement::accept(StatementVisitor& v) { v.visit(*this); }
void WhileStatement::accept(StatementVisitor& v) { v.visit(*this); }
void ForStatement::accept(StatementVisitor& v) { v.visit(*this); }
void ForEachStatement::accept(StatementVisitor& v) { v.visit(*this); }
void ReturnStatement::accept(StatementVisitor& v) { v.visit(*this); }

}
