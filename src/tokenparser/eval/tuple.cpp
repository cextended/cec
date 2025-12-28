#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	std::shared_ptr<TupleExpression> eval_tuple(Tokens::Type till) {
		std::shared_ptr<TupleExpression> tuple = std::make_shared<TupleExpression>();
		do {
			ExprPtr expr = eval_single(Tokens::TOK_SYS_SKIP);
			if(expr)
				tuple->expressions.push_back(expr);
			else break;
		} while(eat(Tokens::TOK_COMMA));

		if(!eat(till)) { /* Error */
			std::cout << "Unexcepted token" << std::endl;
		}

		return tuple;
	}
}
