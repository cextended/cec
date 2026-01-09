#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

namespace Tokenparser {

	DataPipe<Token> *_input_pipe;
	std::shared_ptr<BlockStatement> stm_root;
	int _log_options = EAT_INFO_EAT | EAT_INFO_SKIP;
	Token c_token;

}

}
