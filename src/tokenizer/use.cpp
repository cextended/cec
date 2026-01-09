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
	void use(std::istream &input_stream) {
		_input_stream = &input_stream;
	}

	void use(DataPipe<Token> &output_pipe) {
		_output_pipe = &output_pipe;
	}
}

}
