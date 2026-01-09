#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

namespace Tokenparser {
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
			if(c_token.ttype != Tokens::TOK_SYS_EOF)
				*_input_pipe >> c_token;
			return 1;
		}

		return 0;
	}
}

}
