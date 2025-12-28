#include <segvc/tokenparser.hxx>
	namespace Tokenparser {
	ExprPtr eval0() {
		ExprPtr main_expr = eval1();
		if(main_expr)
			if(eat(Tokens::TOK_ASSIGN))
				return std::make_shared<BinaryExpression>(
					main_expr,
					OPE::ASSIGN,
					eval0());
		return main_expr;
	}
}
