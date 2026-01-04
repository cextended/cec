#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval2() {
		ExprPtr main_expr = evalUnary();
		if(!main_expr) return 0;

		while(true) {
			if(eat(Tokens::TOK_STAR))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::MUL,
							evalUnary());
			else if(eat(Tokens::TOK_SLASH))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::DIV,
							evalUnary());
			else if(eat(Tokens::TOK_MOD))
				main_expr = std::make_shared<BinaryExpression>(
							main_expr,
							OPE::MOD,
							evalUnary());
			else break;
		}
		return main_expr;
	}
}
