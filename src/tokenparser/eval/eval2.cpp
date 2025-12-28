#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval2() {
		ExprPtr main_expr = eval3();
		if(!main_expr) return 0;

		if(eat(Tokens::TOK_STAR))
			return std::make_shared<BinaryExpression>(
						main_expr,
						OPE::MUL,
						eval2());
		else if(eat(Tokens::TOK_SLASH))
			return std::make_shared<BinaryExpression>(
						main_expr,
						OPE::DIV,
						eval2());
		else if(eat(Tokens::TOK_MOD))
			return std::make_shared<BinaryExpression>(
						main_expr,
						OPE::MOD,
						eval2());

		return main_expr;
	}
}
