/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

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

	SemanticException::SemanticException(std::string msg,
	                                     Type expectedType1, Type expectedType2,
	                                     Type actualType,
	                                     yy::position pos):
	InterpreterException(msg + ": expected " + toString(expectedType1) + " or " + toString(expectedType2) + ", got " + toString(actualType),pos) {}

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
