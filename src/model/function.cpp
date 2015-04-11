#include "function.h"

//#include <cstring>
#include <sstream>

namespace stibbons {

Function::Function (vector<string> params) : parameters(params) {}

ValuePtr Function::operator() (AgentPtr agent, TablePtr params) {
	return exec (agent, params);
}

vector<string> Function::getParams (){
	lock_guard<mutex> lock(value_m);

	return parameters;
}

int Function::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Function>(other));
}

int Function::compare(FunctionPtr other) {
	return other.get() - this;
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
