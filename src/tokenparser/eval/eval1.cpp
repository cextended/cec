#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval1() {
		ExprPtr main_expr = eval2();
		if(!main_expr) return 0;

		while(true) {
			if(eat(Tokens::TOK_PLUS))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::ADD,
							eval2());
			else if(eat(Tokens::TOK_MINUS))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::SUB,
							eval2());
			else break;
		}
		return main_expr;
	}
}
