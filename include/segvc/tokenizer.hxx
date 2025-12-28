#pragma once

#include<segvc/datapipe.hxx>
#include<segvc/tokens.hxx>

namespace Tokenizer {

	extern size_t line, line_beg;
	extern bool isSystem;
	extern std::istream *_input_stream;
	extern DataPipe<Token> *_output_pipe;
	extern std::string current_file;

	void use(std::istream &input_stream);
	void use(DataPipe<Token> &output_pipe);

	int proc();

	std::string readLine(std::istream &in);

	void procAlpNum(Token& arg);
	void procSymbol(Token& arg);
	Token readAlpNum(std::istream &in);
	Token readNum(std::istream& in);
	Token readChar(std::istream& in);
	Token readString(std::istream& in);
	Token readSymbol(std::istream& in);
}
