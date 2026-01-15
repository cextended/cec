#include <segvc/tokenparser.hxx>

namespace segvc {

	ExprPtr Tokenparser::evalBinaryLeftToRight(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index) {
		ExprPtr main_expr = eval_order_exec(index + 1);

		bool continueIteration=!!main_expr;
		while(continueIteration) {
			continueIteration=false;
			for(auto [ttype, op]: bindings) {
				if(eat(ttype)) {
					main_expr = std::make_shared<BinaryExpression>(
						main_expr,
						op,
						eval_order_exec(index + 1));

					continueIteration=true;
					break; // break's not necessary but probably improve efficiency.
				}
			}
		}
		return main_expr;
	}

	ExprPtr Tokenparser::evalBinaryRightToLeft(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index) {
		ExprPtr main_expr = eval_order_exec(index + 1);
		
		if(main_expr) {
			for(auto [ttype, op]: bindings) {
				if(eat(ttype)) {
					return std::make_shared<BinaryExpression>(
						main_expr,
						op,
						evalBinaryRightToLeft(bindings, index));
				}
			}
		}
		return main_expr;
	}

}
