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
			{
				{Tokens::TOK_ASSIGN, OPE::ASSIGN},
				{Tokens::TOK_ASSIGN_PLUS, OPE::ASSADD },
				{Tokens::TOK_ASSIGN_MINUS,  OPE::ASSSUB },
				{Tokens::TOK_ASSIGN_MUL,  OPE::ASSMUL },
				{Tokens::TOK_ASSIGN_DIV,  OPE::ASSDIV },
				{Tokens::TOK_ASSIGN_MOD,  OPE::ASSMOD },
				{Tokens::TOK_ASSIGN_AND,  OPE::ASSAND },
				{Tokens::TOK_ASSIGN_OR,   OPE::ASSOR  },
				{Tokens::TOK_ASSIGN_XOR,  OPE::ASSXOR },
				{Tokens::TOK_ASSIGN_SHL,  OPE::ASSSHL },
				{Tokens::TOK_ASSIGN_SHR,  OPE::ASSSHR },
				{Tokens::TOK_ASSIGN_SWAP, OPE::ASSSWAP}
			}
		},

		// TODO: Going to add a special ternary evaulator dunction here

		{ // OP: ||
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_OR, OPE::OROR}
			},
		},
		{ // OP: &&
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_AND, OPE::ANDAND}
			},
		},


		{ // OP: |
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_BIT_OR, OPE::OR}
			},
		},
		{ // OP: ^
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_XOR, OPE::XOR}
			},
		},
		{ // OP: &
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_BIT_AND, OPE::AND}
			},
		},


		{ // OP: ==
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_EQEQ, OPE::EQEQ}
			},
		},
		{ // OP: !=
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_NEQ, OPE::NEQ}
			},
		},


		{ // OP: COMPARE
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_OP_LT,  OPE::COMLT  }, // <
				{Tokens::TOK_OP_RT,  OPE::COMRT  }, // >
				{Tokens::TOK_OP_LTE, OPE::COMLTE }, // <=
				{Tokens::TOK_OP_RTE, OPE::COMRTE }  // >=
			},
		},

		{ // OP: BIT SHIFT
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_SHL,  OPE::SHIFTL  }, // <<
				{Tokens::TOK_SHR,  OPE::SHIFTR  }, // >>
			},
		},

		{ // OP: ADD, SUB
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_PLUS, OPE::ADD},
				{Tokens::TOK_MINUS, OPE::SUB}
			},
		},
		{ // OP: MUL, DIV, MOD
			evalBinaryLeftToRight,
			{
				{Tokens::TOK_STAR, OPE::MUL},
				{Tokens::TOK_SLASH, OPE::DIV},
				{Tokens::TOK_MOD, OPE::MOD}
			},
		},

		// TODO: going'to create another special evualator function because we need to add type cast as well
		{ // OP: Unary prefix
			evalUnaryPrefix,
			{
				{Tokens::TOK_INC, OPE::INCB},
				{Tokens::TOK_DEC, OPE::DECB},
				{Tokens::TOK_PLUS, OPE::POSITIVE},
				{Tokens::TOK_MINUS, OPE::NEGATIVE}
			}
		},
		{ // OP: Unary postfix
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
