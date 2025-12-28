#include <segvc/tokenparser.hxx>

namespace Tokenparser {
	ExprPtr eval_single(Tokens::Type till) {
		ExprPtr expr = eval0(); // We'll modify that func later on
		if(!eat(till)) {
			/* Error */
			std::cout << "Unexpected token" << std::endl;
			return 0;
		}
		return expr;
	}
}
