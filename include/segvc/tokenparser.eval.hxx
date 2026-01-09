#pragma once

namespace segvc {

namespace Tokenparser {

	ExprPtr eval_single(Tokens::Type till);
	std::shared_ptr<TupleExpression> eval_tuple(Tokens::Type till);
	ExprPtr eval(Tokens::Type till);

	ExprPtr evalPrimary(std::vector< std::pair<Tokens::Type, OPE>>&, int);

	ExprPtr evalUnaryPrefix(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);
	ExprPtr evalUnaryPostfix(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);

	ExprPtr evalBinaryLeftToRight(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);
	ExprPtr evalBinaryRightToLeft(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);

	extern struct eval_order_t {
		ExprPtr (*eval_func)(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);
		std::vector< std::pair<Tokens::Type, OPE>> bindings;
	} eval_orders[];

	inline ExprPtr eval_order_exec(int index) {
		auto order = eval_orders[index];
		return order.eval_func(order.bindings, index);
	}
}

}
