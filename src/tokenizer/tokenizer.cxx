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
	size_t line, line_beg;

	bool isSystem;

	std::istream *_input_stream;
	DataPipe<Token> *_output_pipe;

	std::string current_file;
}

}
