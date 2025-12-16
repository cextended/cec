#include <tokenparser/tokenparser.hxx>
#include <tokenparser/expressions.hxx>
#include <qcerrors.hxx>

namespace Tokenparser {

	std::istream  *_input_stream;
	std::shared_ptr<BlockStatement> stm_root;
	int _log_options = EAT_INFO_EAT | EAT_INFO_SKIP;

	void use(std::istream &input_stream) {
	        _input_stream = &input_stream;
	}

	void use(std::shared_ptr<BlockStatement> _stm_root) {
		stm_root = _stm_root;
	}

	void use(int log_options) {
		_log_options = log_options;;
	}

	Token c_token;

	int eat(Tokens::Type ttype) { // return 1 if match, 0 if not match

		std::string token_name = c_token.name;
		if(ttype == Tokens::TOK_SYS_EOF)
			token_name = " < End of File >";
		else if(ttype == Tokens::TOK_NUMBER_LITERAL ||
			ttype == Tokens::TOK_CHAR_LITERAL ||
			ttype == Tokens::TOK_STRING_LITERAL)
				token_name = " < Literal > " + token_name;

		if(ttype == Tokens::TOK_SYS_SKIP) {
			if(_log_options & EAT_INFO_SKIP )
				std::cout << "Skip: " << c_token.line << ":" << token_name << std::endl;
			return 1;
		}

		if(c_token.ttype == ttype) {
			if(_log_options & EAT_INFO_EAT)
				std::cout << "Eat : " << c_token.line << ":" << token_name << std::endl;
			_input_stream >> c_token;
			return 1;
		}

		return 0;
	}

	uint8_t getPVarT(const std::string& str) {
		if(str == "u1")
			return VAR_U1;

		else if(str == "u8")
			return VAR_U8;
		else if(str == "i8")
			return VAR_I8;
		else if(str == "c8")
			return VAR_C8;

		else if(str == "u16")
			return VAR_U16;
		else if(str == "i16")
			return VAR_I16;
		else if(str == "c16")
			return VAR_C16;

		else if(str == "u32")
			return VAR_U32;
		else if(str == "i32")
			return VAR_I32;
		else if(str == "c32")
			return VAR_C32;
		else if(str == "f32")
			return VAR_F32;

		else if(str == "u64")
			return VAR_U64;
		else if(str == "i64")
			return VAR_I64;
		else if(str == "f64")
			return VAR_F64;

		else if(str == "u128")
			return VAR_U128;
		else if(str == "i128")
			return VAR_I128;
		else if(str == "f128")
			return VAR_F128;

		else if(str == "usize")
			return VAR_USIZE;
		else if(str == "isize")
			return VAR_ISIZE;

		else if(str == "bool")
			return VAR_BOOL;

		return VAR_UNDEFINED;
	}

	int eatTyper(std::shared_ptr<Typer>& c_typer, bool followAll) {
		while(1) {
			if(c_token.ttype == Tokens::TOK_TYPE) {
				uint8_t vtype = getPVarT(c_token.name);
				eat(Tokens::TOK_TYPE);

				if(c_typer->vtype)
					std::cerr << "Warning! Declaration with multiple types, last one will be count!!" << std::endl;

				c_typer->vtype = vtype;
			}
			else if(eat(Tokens::TOK_KEY_NDET))
				c_typer->spec |= (1 << SPEC_NDET);
			else if(eat(Tokens::TOK_KEY_MUT))
				c_typer->spec |= (1 << SPEC_MUT);
			else if(eat(Tokens::TOK_KEY_INLINE))
				c_typer->spec |= (1 << SPEC_INL);
			else if(eat(Tokens::TOK_KEY_EXTERN))
				c_typer->spec |= (1 << SPEC_EXT);
			else if(eat(Tokens::TOK_KEY_VOLATILE))
				c_typer->spec |= (1 << SPEC_VOL);
			else if(eat(Tokens::TOK_DEL_PARANL)) {
				std::shared_ptr<BlockStatement> body = std::make_shared<BlockStatement>();
				if( !eatDec(body, DeclarationType::UNDEFINED) ) {
					/* error */
				}
				if(!eat(Tokens::TOK_DEL_PARANR)) {
					/* error */
				}
				std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();
				ptr_typer->func_params = body->childs;
				if(c_typer)
					c_typer->respect_typer = ptr_typer;
				ptr_typer->vtype = VAR_FUN;
				c_typer = ptr_typer;
			} else if(eat(Tokens::TOK_DEL_SBRACL)) {
				ExprPtr expr = eval(Tokens::TOK_DEL_SBRACR);
				if(!expr) {
					/* error */
				}
				std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();
				ptr_typer->sizer = expr;
				if(c_typer)
					c_typer->respect_typer = ptr_typer;
				c_typer->vtype = VAR_ARRAY;
				c_typer = ptr_typer;
			} else if(followAll && eat(Tokens::TOK_STAR)) {
				std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();
				if(c_typer)
					c_typer->respect_typer = ptr_typer;
				c_typer->vtype = VAR_POINTER;
				c_typer = ptr_typer;
                        } else break;
		};

/*
*		I'll use Tokens::TOK_SYS_SKIP instead of Tokens::TOK_SEMICOLON because I wan't to get rid of semicolons without breaking C syntax as much as posible .
*
*		I'll set initializer to the highest typer and it's 'Tokens Typer::ttype' should be equals to Tokens::VAR_DEC .
*/

		return c_typer->vtype;
	};

	int getPSize(std::string s) {
		return 0;
	}

	int eatDec(
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
			if(!eatTyper(c_typer, true)) {
				/* error */
			}

			if(eat(Tokens::TOK_ASSIGN)) {
				hasAssignments = true;
				ExprPtr expr = std::make_shared<BinaryExpression>(
			                std::make_shared<VariableExpression>(var_name),
			                OPE::ASSIGN,
			                eval_single(Tokens::TOK_SYS_SKIP)
			        );
				var_list.push_back({
					var_name,
					c_typer,
					expr
				});
			}

		} while(eat(Tokens::TOK_COMMA));

		std::shared_ptr<Typer> master_typer = nullptr;
		ExprPtr master_assign = nullptr;
		if(eat(Tokens::TOK_COLON)) {
			master_typer = std::make_shared<Typer>();
			if(!eatTyper(master_typer, true)) {
				/* error */
			}

			if(eat(Tokens::TOK_ASSIGN)) {
				if(hasAssignments) {
					/* warning */
					// Some variables has already been assigned!
				}
				master_assign = eval_tuple(Tokens::TOK_SYS_SKIP);
			}
		}

		for(auto [var_name, typer, expr]: var_list) {
			if(master_typer) {
				master_typer->respect_typer = typer;
				typer = master_typer;
			}

			std::shared_ptr<DeclarationStatement> decStm = std::make_shared<DeclarationStatement>();
                        decStm->name = var_name;
			decStm->dec_type = dec_type;
                        decStm->type_spec = typer;
                        decStm->initializer = master_assign ? master_assign : expr;
                        parent->childs.push_back(decStm);
		}

		return 1;
	}

	int eatFnDec(
		std::shared_ptr<BlockStatement> parent,
		DeclarationType dec_type
	) {
		if(c_token.ttype != Tokens::TOK_IDENTIFIER)
			return 0;

		std::string var_name = c_token.name;
		eat(Tokens::TOK_IDENTIFIER);

		std::shared_ptr<Typer> c_typer = std::make_shared<Typer>();
		if(!eatTyper(c_typer, true)) {
			/* error */
		}

		// If therese no parameters specified, set it as 0 parameters
		if(c_typer->vtype != VAR_FUN) {
			std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();
			ptr_typer->vtype = VAR_FUN;
			if(c_typer)
				c_typer->respect_typer = ptr_typer;
			c_typer = ptr_typer;
		}

		if(!eat(Tokens::TOK_DEL_CBRACL)) {
			/* error */
			return 0;
		}
		std::shared_ptr<FunctionDeclarationStatement> decStm = std::make_shared<FunctionDeclarationStatement>();
		decStm->name = var_name;
		decStm->dec_type = dec_type;
		decStm->type_spec = c_typer;
		decStm->body = std::make_shared<BlockStatement>();
		if(proc_body(decStm->body, Tokens::TOK_DEL_CBRACR)) {
			/* error */
			return 0;
		}
		return 1;
	}


	/*
	* Return values and their meanings:
	*   0 : No catch
	*   1 : Problem caught
	*   2 : Finish
	*/

	int proc(std::shared_ptr<BlockStatement> parent, const bool _inline) {
		if(eat(Tokens::TOK_DEL_CBRACL)) {
			if(proc_body(parent, Tokens::TOK_DEL_CBRACR)) return 1;
			return 0;
		}

		DeclarationType dec_type = DeclarationType::UNDEFINED;

		if(eat(Tokens::TOK_KEY_CONST)) {
			dec_type = DeclarationType::CONST;
		} else if(eat(Tokens::TOK_KEY_STATIC)) {
			dec_type = DeclarationType::STATIC;
		}

		if(eat(Tokens::TOK_KEY_FN)) {
			if(!eatFnDec(parent, dec_type)) {
				/* error */
				return 1;
			}

			return 0;
		} else if(((dec_type != DeclarationType::UNDEFINED) || eat(Tokens::TOK_KEY_LET)) && eatDec(parent, dec_type)) {
			if(_inline) {
				/* Warning */
				/* Maybe can be solved with -O1 or -O2 (I'll add these options later) */
			}
			return 0;
		}

		if(dec_type) {
			/* error */
			return 1;
		}

		if(eat(Tokens::TOK_KEY_RETURN)) {
			std::shared_ptr<ReturnStatement> stm = std::make_shared<ReturnStatement>();
			stm->expr = eval(Tokens::TOK_SYS_SKIP);
			return 0;
		}

		ExprPtr expr = eval(Tokens::TOK_SYS_SKIP);
		if(expr) {
			std::shared_ptr<ExpressionStatement> stm = std::make_shared<ExpressionStatement>();
			stm->expr = expr;
			parent->childs.push_back(stm);
			return 0;
		}

		if(eat(Tokens::TOK_SEMICOLON))
			return 0;

		return 2;
	}

	int proc_body(std::shared_ptr<BlockStatement> parent, Tokens::Type end_token) {
		while(true) {
			int cons = proc(parent, false);
			if(cons == 1)
				return 0;
			else if(cons == 2) break;
		}

		if(!eat(end_token)) { /* Error */
			std::cout << "Unexpected token: " << c_token.name << std::endl;
			return 1;
		}
		return 0;
	}

	int proc() {
		if(!_input_stream || !stm_root) return 1;
		_input_stream >> c_token;
		return proc_body(stm_root);
	}
}
