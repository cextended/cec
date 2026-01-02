#pragma once

#include<segvc/util/datapipe.hxx>
#include<vector>
#include<segvc/tokens.hxx>
#include<segvc/expressions.hxx>
#include<segvc/tokenparser.eval.hxx>

namespace Tokenparser {

	extern DataPipe<Token> *_input_pipe;
	extern std::shared_ptr<BlockStatement> stm_root;
	extern int _log_options;
	extern Token c_token;

	enum {
		EAT_INFO_EAT = 0b1,
		EAT_INFO_SKIP = 0b10,
	};

	void use(DataPipe<Token> &input_pipe);
	void use(std::shared_ptr<BlockStatement> stm_root);
	void use(int log_options);

	uint8_t getPVarT(const std::string& str);

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

        int eatWhileStatement(
		std::shared_ptr<BlockStatement> parent,
		std::shared_ptr<BlockStatement> leadingBlock = nullptr
	);

        int proc(std::shared_ptr<BlockStatement> parent, const bool _inline = true, const bool subscope = false);
        int proc_body(std::shared_ptr<BlockStatement> parent, Tokens::Type end_token = Tokens::TOK_SYS_EOF);
	int proc();
}
