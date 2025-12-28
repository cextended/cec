#pragma once

#include<segvc/datapipe.hxx>
#include<segvc/tokens.hxx>

namespace Tokenizer {

	void use(std::istream &input_stream);
	void use(DataPipe<Token> &output_pipe);

	int proc();
}
