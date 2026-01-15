#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

	int Tokenparser::eatDec(
		std::shared_ptr< BlockStatement > parent,
		DeclarationType dec_type
	) {
		bool hasAssignments = false;
		std::vector< std::tuple< std::string, std::shared_ptr<Typer>, ExprPtr > > var_list;
		std::vector< std::shared_ptr<Typer> > t_list;

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

			var_list.push_back({
				var_name,
				c_typer,
				initializer
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

		int index=0;

		std::shared_ptr<MultipleDeclarationStatement> mulDecStm = std::make_shared<MultipleDeclarationStatement>();
		mulDecStm->initializer = master_assign;

		for(auto [var_name, typer, initializer]: var_list) {
			if(master_typer) {
				master_typer->respect_typer = typer;
				typer = master_typer;
			}

			std::shared_ptr<DeclarationStatement> decStm = std::make_shared<DeclarationStatement>();
                        decStm->name = var_name;
                        decStm->type_spec = typer;
			decStm->dec_type = dec_type;

			/**
			 *  Must specify the variable type if it's const
			 */
			if(decStm->dec_type == DeclarationType::CONST && !typer) {
				std::cout << "Must specify variable type for constants!" << std::endl;
			}

			if(master_assign) {
				if(initializer)
					/* warning */
					// Some variables has already been assigned!
					std::cout << "Warning: This variables has already been assigned!" << std::endl;
				mulDecStm->initializer = master_assign;
				mulDecStm->list.push_back(decStm);
			} else {
				decStm->initializer = initializer;
	                        parent->childs.push_back(decStm);
			}
		}

		if(mulDecStm->initializer = master_assign)
			parent->childs.push_back(mulDecStm);

		return 1;
	}

}
