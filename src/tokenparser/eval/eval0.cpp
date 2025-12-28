#include <segvc/tokenparser.hxx>
	namespace Tokenparser {
	ExprPtr eval() {
		ExprPtr main_expr = eval1();
		if(main_expr)
			if(eat(Tokens::TOK_ASSIGN))
				return std::make_shared<BinaryExpression>(
					main_expr,
					OPE::ASSIGN,
					eval());
		return main_expr;
	}
}
