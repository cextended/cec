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
	Token readAlpNum(std::istream &in) {
		size_t start_index=in.tellg();

		std::string ret;

		int curr = in.peek();
		while(std::isalnum(curr) || curr == '_') {
			ret += static_cast<char>(in.get());
			curr = in.peek();
		}

		Token tok;
		tok.name = ret;
		tok.line = line;
		tok.endOffset = start_index + ret.size();
		tok.column = tok.endOffset - line_beg + 1;
		tok.startOffset = start_index;

		return tok;
	}
}

}
