#include <segvc/expressions.hxx>

BinaryExpression::BinaryExpression(ExprPtr left, OPE op, ExprPtr right) : left(left), op(op), right(right) {}
UnaryExpression::UnaryExpression(ExprPtr te, OPE op) : te(te), op(op) {}
LiteralExpression::LiteralExpression(int ltype, std::string value) : ltype(ltype), value(value) {}
VariableExpression::VariableExpression(std::string name) : name(name) {}
MemberExpression::MemberExpression(ExprPtr parent, std::string name) : parent(parent), VariableExpression(name) {}
SubscriptExpression::SubscriptExpression(ExprPtr parent, ExprPtr index) : parent(parent), index(index) {}
FunctionCallExpression::FunctionCallExpression(ExprPtr function, std::shared_ptr<TupleExpression> params) : function(function), params(params) {}
