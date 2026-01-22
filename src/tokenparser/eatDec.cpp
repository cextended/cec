#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>
#include <segvc/util/concat.hxx>

namespace segvc {

	int Tokenparser::eatDec(
		std::shared_ptr< BlockStatement > parent,
		DeclarationType dec_type
	) {
		bool hasAssignments = false;

		std::shared_ptr<DeclarationStatement> decStm = std::make_shared<DeclarationStatement>();
		parent->childs.push_back(decStm);

		do {
			if(c_token.ttype != Tokens::TOK_IDENTIFIER) {
				break;
			}

			std::string var_name = c_token.name;
			eat(Tokens::TOK_IDENTIFIER);

			std::shared_ptr<Typer> c_typer = std::make_shared<Typer>();


			/**
			 *  No need to check if it's nullptr or not by default,
			 *  Only if it's constant
			 */
			eatTyper(c_typer, true);


			ExprPtr initializer = nullptr;
			if(eat(Tokens::TOK_ASSIGN)) {
				hasAssignments = true;

				initializer = eval_single(Tokens::TOK_SYS_SKIP);
				if(!initializer) {
					/* error */
					std::cout << "No value passed after '=' !" << std::endl;
					return 0;
				}
			}

			decStm->variables.push_back({
				var_name,
				VariableEntry {
					c_typer,
					initializer
				}
			});

		} while(eat(Tokens::TOK_COMMA));

		std::shared_ptr<Typer> master_typer = nullptr;
		ExprPtr master_assign = nullptr;
		if(eat(Tokens::TOK_COLON)) {
			master_typer = std::make_shared<Typer>();
			if(!eatTyper(master_typer, true)) {
				/* error */
			}

			if(eat(Tokens::TOK_ASSIGN)) {
				master_assign = eval_single(Tokens::TOK_SYS_SKIP);
			}
		}


		decStm->dec_type = dec_type;
		decStm->master_initializer = master_assign;

		for(auto [var_name, entry]: decStm->variables) {

			if(master_typer) {
				concat(master_typer, entry.typer);
				entry.typer = master_typer;
			}
		}

		return 1;
	}

}
