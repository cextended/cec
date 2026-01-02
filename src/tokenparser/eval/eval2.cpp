#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval2() {
		ExprPtr main_expr = eval3();
		if(!main_expr) return 0;

		while(true) {
			if(eat(Tokens::TOK_STAR))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::MUL,
							eval3());
			else if(eat(Tokens::TOK_SLASH))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::DIV,
							eval3());
			else if(eat(Tokens::TOK_MOD))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::MOD,
							eval3());
			else break;
		}
		return main_expr;
	}
}
