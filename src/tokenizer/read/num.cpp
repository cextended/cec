#include <segvc/tokens.hxx>
#include <segvc/tokenizer.hxx>
#include <string>
#include <cstring>
#include <cstdint>
#include <cctype>
#include <segvc/qcerrors.hxx>
#include <iostream>
#include <unordered_map>

namespace segvc {

namespace Tokenizer {
	inline int toNumber(int c) {
		if(c >= '0' && c <= '9')
			return c - '0';
		else if(c >= 'a' && c <= 'f')
			return c - 'a' + 10;
		else if(c >= 'A' && c <= 'F')
			return c - 'A' + 10;
		return 0;
	}


	Token readNum(std::istream& in) {
		size_t start_index=in.tellg();
		size_t end_index = 0;

		std::string ret;

	        int curr = in.peek();

		bool continueReading=false;
		if(curr == '0') {
			in.ignore(), curr = in.peek();

			if(curr == 'x' || curr == 'X') {
				ret = "0x";
				in.ignore(), curr = in.peek();
				while(std::isxdigit(curr) || curr == '.' || curr == '_') {
					if(curr == '_') {
						++end_index;
						in.ignore(), curr = in.peek();
						continue;
					}

					ret += "" + toNumber(in.get());
					curr = in.peek();
				}
			} else if(curr == 'b' || curr == 'B') {
				ret = "0b";
				in.ignore(), curr = in.peek();
				while(curr == '0' || curr == '1' || curr == '.' || curr == '_') {
					if(curr == '_') {
						++end_index;
						in.ignore(), curr = in.peek();
						continue;
					}

					ret += in.get();
					curr = in.peek();
				}

			} else
				continueReading = true, ret = "0";
		} else
			continueReading = true;

		if(continueReading)
		while(std::isdigit(curr) || curr == '.' || curr == '_') {
			if(curr == '_') {
				++end_index;
				in.ignore(), curr = in.peek();
				continue;
			}
			ret += in.get();
			curr = in.peek();
	        }

		end_index += ret.size();


	        Token tok;
	        tok.name = ret;
	        tok.line = line;
	        tok.endOffset = end_index;
	        tok.column = tok.endOffset - line_beg + 1;
	        tok.startOffset = start_index;
		tok.ttype = Tokens::TOK_NUMBER_LITERAL;

	        return tok;
	}
}

}
