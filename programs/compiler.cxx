#include <cstdlib>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include<thread>

#include <segvc/tokenizer.hxx>
#include <segvc/tokenparser.hxx>
/*
inline
std::string getExecutablePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
}

inline
std::string getExecutableDir() {
    std::string path = getExecutablePath();
    return path.substr(0, path.find_last_of('/'));
}
*/


int main(int argc, char *argv[]) {
	std::string in, out="a.out";

	for(int i=1; i < argc; i++) {
                std::string arg = argv[i];
                if(arg == "-o")
                        if(++i < argc) {
                                arg = argv[i];
                                if(arg != "-") {
					out = arg;
                                }
                        } else {
                                std::cerr << "File path not given after '-o' option" << std::endl;
                                return 1;
                        }
                else {
                        in = arg;
                }
        }

	std::istream *ins;
	if(in.empty())
		ins = &std::cin;
	else
		ins = new std::ifstream(in);

	Tokenizer::use(*ins);

	DataPipe<Token> lex2par;
	Tokenizer::use(lex2par);
	Tokenparser::use(lex2par);

	std::shared_ptr<BlockStatement> stm_root = std::make_shared<BlockStatement>();
	Tokenparser::use(stm_root);

	std::thread lexTh(static_cast<int(*)()>(Tokenizer::proc));
	std::thread parTh(static_cast<int(*)()>(Tokenparser::proc));

	lexTh.join();
	parTh.join();

	if(ins != &std::cin)
		delete ins;
	return 0;
}
