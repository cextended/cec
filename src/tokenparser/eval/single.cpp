#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval_single(Tokens::Type till) {
		ExprPtr expr = eval_order_exec(0);
		if(!eat(till)) {
			/* Error */
			std::cout << "Unexpected token" << std::endl;
			return 0;
		}
		return expr;
	}
}
