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

	Token Tokenizer::readChar(std::istream& in) {
		size_t start_index = in.tellg();
		in.get();
		char c = in.peek();
		if(c == '\\') {
			in.get();
			c = in.peek();
			switch(c) {
				case 'n':
					c =  '\n';
					break;
				case 't':
					c = '\t';
					break;
				case '0':
					c = '\0';
					break;
				case '\\':
					c = '\\';
					break;
				case '\'':
	                                c = '\'';
					break;
			}
		}
		in.get();

		Token tok;
		std::string(1, static_cast<char>(c));
	        tok.line = line;
	        tok.column = static_cast<size_t>(in.tellg()) - line_beg + 1;
	        tok.startOffset = start_index;
	        tok.endOffset = static_cast<size_t>(in.tellg());
		tok.ttype = Tokens::TOK_CHAR_LITERAL;

		return tok;
	}

}
