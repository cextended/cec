#include <segvc/tokenparser.hxx>

namespace Tokenparser {

	ExprPtr eval3() {
		if(eat(Tokens::TOK_INC)) {

			ExprPtr main_expr = eval3();

			if(!main_expr) return 0; /* Error */

			return std::make_shared<UnaryExpression>(main_expr, OPE::INCB);
		} else if(eat(Tokens::TOK_DEC)) {

			ExprPtr main_expr = eval3();

			if(!main_expr) return 0; /* Error */

			return std::make_shared<UnaryExpression>(main_expr, OPE::DECB);
		} else if(c_token.ttype == Tokens::TOK_IDENTIFIER) {
			std::shared_ptr<VariableExpression> var_expr = std::make_shared<VariableExpression>(c_token.name);
			eat(Tokens::TOK_IDENTIFIER);

			if(eat(Tokens::TOK_DEL_SBRACL)) {
				ExprPtr index = eval(Tokens::TOK_DEL_SBRACR);
                                std::shared_ptr<SubscriptExpression> member = std::make_shared<SubscriptExpression>(var_expr, index);
				return member;
			} else if(eat(Tokens::TOK_DEL_PARANL)) {
				std::shared_ptr<TupleExpression> tuple = eval_tuple(Tokens::TOK_DEL_PARANR);
				std::shared_ptr<UnaryExpression> func = std::make_shared<UnaryExpression>(var_expr, OPE::FUNCALL);
				func->tuple = tuple;
				return func;
			} else if(eat(Tokens::TOK_INC))
				return std::make_shared<UnaryExpression>(var_expr, OPE::INCA);
			else if(eat(Tokens::TOK_DEC))
				return std::make_shared<UnaryExpression>(var_expr, OPE::DECA);


			return var_expr;
		} else if(eat(Tokens::TOK_DEL_PARANL))
			return eval(Tokens::TOK_DEL_PARANR);
		else if(eat(Tokens::TOK_DEL_SBRACL))
			return eval_tuple(Tokens::TOK_DEL_SBRACR);
		else if(c_token.ttype == Tokens::TOK_STRING_LITERAL) {
			std::string name = c_token.name;
			eat(Tokens::TOK_STRING_LITERAL);

			return std::make_shared<LiteralExpression>(LIT_STRING, name);
		} else if(c_token.ttype == Tokens::TOK_NUMBER_LITERAL) {
			std::string name = c_token.name;
			eat(Tokens::TOK_NUMBER_LITERAL);

			return std::make_shared<LiteralExpression>(LIT_NUMBER, name);
		} else if(c_token.ttype == Tokens::TOK_CHAR_LITERAL) {
			std::string name = c_token.name;
			eat(Tokens::TOK_CHAR_LITERAL);

			return std::make_shared<LiteralExpression>(LIT_CHAR, name);
		}

		return 0;
	}
}
