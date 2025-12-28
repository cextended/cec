#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace Tokenparser {
	int eatWhileStatement(std::shared_ptr<BlockStatement> parent, std::shared_ptr<BlockStatement> leadingBlock) {
		std::shared_ptr<WhileStatement> stmRet = std::make_shared<WhileStatement>();
		stmRet->lead = leadingBlock;

		ExprPtr condition = eval(Tokens::TOK_SYS_SKIP);
		if(!condition) {
			/* error */
			return 0;
		}

		stmRet->condition = condition;
		std::shared_ptr<BlockStatement> body = std::make_shared<BlockStatement>();
		if(proc(body, Tokens::TOK_SYS_SKIP)) {
			/* error */
			return 0;
		}
		stmRet->body = body;

		if(eat(Tokens::TOK_KEY_THEN)) {
			std::shared_ptr<BlockStatement> trailingBlock = std::make_shared<BlockStatement>();
			if(proc(trailingBlock)) {
				/* error */
				return 0;
			}
			stmRet->trail = trailingBlock;
		}

		parent->childs.push_back(stmRet);
		return 1;
	}
}
