#pragma once

#include<util/datapipe.hxx>
#include<tokenizer/tokens.hxx>

namespace Tokenizer {

	void use(std::istream &input_stream);
	void use(DataPipe<Token> &output_pipe);

	int proc();
}
