#include "semantic-exception.h"

namespace stibbons {
    SemanticException::SemanticException(const char* msg, yy::position pos): InterpreterException(msg,pos) {}

	SemanticException::SemanticException(std::string msg,
	                                     Type expectedType,
	                                     Type actualType,
	                                     yy::position pos):
	InterpreterException(msg + ": expected " + toString(expectedType) + ", got " + toString(actualType),pos) {}

	SemanticException::SemanticException(std::string msg,
	                                     Type expectedType1, Type expectedType2,
	                                     Type actualType1, Type actualType2,
	                                     yy::position pos):
	InterpreterException(msg + ": expected " + toString(expectedType1) + " and " + toString(expectedType2) + ", got " + toString(actualType1) + " and " + toString(actualType2),pos) {}

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
