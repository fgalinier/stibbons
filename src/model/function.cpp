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

#include "function.h"

//#include <cstring>
#include <sstream>

namespace stibbons {

Function::Function (vector<string> params) : parameters(params) {}

ValuePtr Function::operator() (AgentPtr agent, TablePtr params) {
	return exec (agent, params);
}

vector<string> Function::getParams (){
	return parameters;
}

double Function::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Function>(other));
}

double Function::compare(FunctionPtr other) {
	return this - other.get();
}

string Function::toString () {
	std::ostringstream oss;

	oss << "function(";
	for (size_t i = 0 ; i < parameters.size() ; i++)
		oss << (i == 0 ? "" : ", ") << parameters[i];
	oss << ")";

	return oss.str();
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
