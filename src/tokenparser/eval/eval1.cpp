#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval1() {
		ExprPtr main_expr = eval2();
		if(!main_expr) return 0;

		if(eat(Tokens::TOK_PLUS))
			return std::make_shared<BinaryExpression>(
						main_expr,
						OPE::ADD,
						eval1());
		else if(eat(Tokens::TOK_MINUS))
			return std::make_shared<BinaryExpression>(
						main_expr,
						OPE::SUB,
						eval1());

		return main_expr;
	}
}
