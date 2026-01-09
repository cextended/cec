#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

namespace Tokenparser {
	void use(DataPipe<Token> &input_pipe) {
	        _input_pipe = &input_pipe;
	}

	void use(std::shared_ptr<BlockStatement> _stm_root) {
		stm_root = _stm_root;
	}

	void use(int log_options) {
		_log_options = log_options;;
	}
}

}
