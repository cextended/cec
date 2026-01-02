#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace Tokenparser {
	int eatForStatement(std::shared_ptr<BlockStatement> parent, std::shared_ptr<BlockStatement> leadingBlock) {
		std::shared_ptr<BasicForStatement> stmRet;
		std::shared_ptr<BlockStatement> decs = std::make_shared<BlockStatement>();
		if(!eatDec(decs, DeclarationType::UNDEFINED)) {
			/* error */
			return 0;
		} else if(eat(Tokens::TOK_KEY_IN)) {
			ExprPtr exp = eval(Tokens::TOK_SYS_SKIP);
			if (!exp) {
				/* error */
				return 0;
			}
			std::shared_ptr<ForEachStatement> stm = std::make_shared<ForEachStatement>();
			stm->init = decs;
			stm->lead = leadingBlock;
			stm->iterable = exp;
			stmRet = stm;
		} else if(eat(Tokens::TOK_SEMICOLON)) {
			ExprPtr condition = eval(Tokens::TOK_SYS_SKIP);
			std::shared_ptr<BlockStatement> update = std::make_shared<BlockStatement>();
			if(!condition) {
				/* error */
				return 0;
			}
			if(eat(Tokens::TOK_SEMICOLON)) { // It's optional
				if(proc(update, true, true)) {
					return 0;
				}
			}

			std::shared_ptr<ForStatement> stm = std::make_shared<ForStatement>();
			stm->init = decs;
			stm->lead = leadingBlock;
			stm->update = update;
			stmRet = stm;
		} else {
			/* error */
			std::cerr << "Unexpected token '" << c_token.name << "', expected 'in' or ';'" << std::endl;
			return 0;
		}

		std::shared_ptr<BlockStatement> body = std::make_shared<BlockStatement>();
		if(proc(body, true, true)) {
			/* error */
			return 0;
		}
		stmRet->body = body;

		if(eat(Tokens::TOK_KEY_THEN)) {
			std::shared_ptr<BlockStatement> trailingBlock = std::make_shared<BlockStatement>();
			if(proc(trailingBlock, true, true)) {
				/* error */
				return 0;
			}
			stmRet->trail = trailingBlock;
		}

		parent->childs.push_back(stmRet);
		return 1;
	}
}
