#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval(Tokens::Type till) {
		ExprPtr main_expr = eval_single(Tokens::TOK_SYS_SKIP);
		if(main_expr) while(eat(Tokens::TOK_COMMA)) {
			ExprPtr expr = std::make_shared<BinaryExpression>(main_expr, OPE::COMMA, eval_single(Tokens::TOK_SYS_SKIP));
			if(expr)
				main_expr = expr;
			else break;
		}

		if(!eat(till)) { /* Error */
			std::cout << "Unexcepted token" << std::endl;
		}

		return main_expr;
	}

	eval_order_t eval_orders[] {
		{
			evalBinaryRightToLeft,
			{{
			Tokens::TOK_ASSIGN, OPE::ASSIGN
			}}
		},
		{
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_PLUS, OPE::ADD},
				{Tokens::TOK_MINUS, OPE::SUB}
			},
		},
		{
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_STAR, OPE::MUL},
				{Tokens::TOK_SLASH, OPE::DIV}
			},
		},
		{
			evalUnaryPrefix,
			{
				{Tokens::TOK_INC, OPE::INCB},
				{Tokens::TOK_DEC, OPE::INCB}
			}
		},
		{
			evalUnaryPostfix,
			{
				{Tokens::TOK_INC, OPE::INCA},
				{Tokens::TOK_DEC, OPE::INCA}
			}
		},
		{
			evalPrimary,
			{}
		}
	};
}
