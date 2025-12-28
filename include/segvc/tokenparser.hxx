#pragma once

#include<util/datapipe.hxx>
#include<vector>
#include<tokenizer/tokens.hxx>
#include<tokenparser/expressions.hxx>

namespace Tokenparser {

	enum {
		EAT_INFO_EAT = 0b1,
		EAT_INFO_SKIP = 0b10,
	};

	void use(DataPipe<Token> &input_pipe);
	void use(std::shared_ptr<BlockStatement> stm_root);
	void use(int log_options);

	uint8_t getPVarT(const std::string& str);

	ExprPtr eval_single(Tokens::Type till);
	std::shared_ptr<TupleExpression> eval_tuple(Tokens::Type till);
	ExprPtr eval(Tokens::Type till);

	int eat(Tokens::Type ttype);
	int eatTyper(std::shared_ptr<Typer>& c_typer, bool followAll);
	int eatDec(
		std::shared_ptr<BlockStatement> parent,
		DeclarationType dec_type
	);

	int eatFnDec(
		std::shared_ptr<BlockStatement> parent,
		DeclarationType dec_type
	);

        int eatForStatement(
		std::shared_ptr<BlockStatement> parent,
		std::shared_ptr<BlockStatement> leadingBlock = nullptr
	);

        int proc(std::shared_ptr<BlockStatement> parent, const bool _inline = true);
        int proc_body(std::shared_ptr<BlockStatement> parent, Tokens::Type end_token = Tokens::TOK_SYS_EOF);
	int proc();
}
