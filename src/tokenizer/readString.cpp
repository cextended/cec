#include <segvc/tokens.hxx>
#include <segvc/tokenizer.hxx>
#include <string>
#include <cstring>
#include <cstdint>
#include <cctype>
#include <segvc/qcerrors.hxx>
#include <iostream>
#include <unordered_map>

namespace Tokenizer {
	Token readString(std::istream& in) {
		size_t start_index = static_cast<size_t>(in.tellg());
		std::string ret;

		in.get(); // opening '"'

		while (true) {
		int ch = in.get();
		if (ch == EOF || ch == '"') break;

		if (ch == '\\') {
			ch = in.get(); // next escaped char
			switch (ch) {
				case 'n':
					ret += '\n';
					break;
				case 't':
					ret += '\t';
					break;
				case '0':
					ret += '\0';
					break;
				case '\\':
					ret += '\\';
					break;
				case '"':
					ret += '"';
					break;
				default:
					ret += '\\';
					if (ch != EOF) ret += static_cast<char>(ch);
					break;
				}
			} else {
				ret += static_cast<char>(ch);
			}
		}

		size_t end_index = static_cast<size_t>(in.tellg());

		Token tok;
		tok.name = ret;
		tok.line = line;
		tok.column = start_index - line_beg + 1;
		tok.startOffset = start_index;
		tok.endOffset = end_index;
		tok.ttype = Tokens::TOK_STRING_LITERAL;

		return tok;
	}
}
