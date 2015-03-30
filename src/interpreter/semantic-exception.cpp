#include "semantic-exception.h"

namespace stibbons {
    SemanticException::SemanticException(const char* msg, yy::position pos): InterpreterException(msg,pos) {}

  	const char* SemanticException::what() const throw() {
		return InterpreterException::what();
  	}
}
/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: t
 * truncate-lines: 1
 * End:
 *
 * vim:set ft=cpp ts=4 sw=4 sts=4
 */
