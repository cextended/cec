#pragma once
ExprPtr eval_single(Tokens::Type till);
std::shared_ptr<TupleExpression> eval_tuple(Tokens::Type till);
ExprPtr eval(Tokens::Type till);


#define DEFINE_EVAL(n) ExprPtr eval##n();
DEFINE_EVAL()
DEFINE_EVAL(1)
DEFINE_EVAL(2)
DEFINE_EVAL(3)
