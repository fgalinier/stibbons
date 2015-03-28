#include "interpreter-exception.h"

namespace stibbons {
	InterpreterException::InterpreterException(const char* msg, yy::position pos): msg(msg), pos(pos) {}

	const char* InterpreterException::what() const throw() {
		std::ostringstream oss; 
		oss<<msg<<" at "<<pos.line<<":"<<pos.column<<".";
		return oss.str().c_str();
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
