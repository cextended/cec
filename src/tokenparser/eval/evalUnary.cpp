#include <segvc/tokenparser.hxx>

namespace Tokenparser {

	ExprPtr evalUnaryPrefix(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index) {
		for(auto [ttype, op]: bindings)
			if(eat(ttype)) {
				ExprPtr main_expr = evalUnaryPrefix(bindings, index);

				if(!main_expr) return 0; /* Error */

				return std::make_shared<UnaryExpression>(main_expr, op);
			}

		return eval_order_exec(index+1);
	}

	ExprPtr evalUnaryPostfix(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index) {
		ExprPtr main_expr = eval_order_exec(index + 1);

		bool continueIteration=!!main_expr;
		while(continueIteration) {
			continueIteration=false;
			for(auto [ttype, op]: bindings)
				if(eat(ttype)) {
					main_expr = std::make_shared<UnaryExpression>(main_expr, op);
					continueIteration=true;
					break; // break's not necessary but probably improve efficiency.
				}
		}
		return main_expr;
	}
}
