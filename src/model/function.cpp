#include "function.h"

//#include <cstring>
#include <sstream>

namespace stibbons {

Function::Function (vector<string> params) : parameters(params) {}

Value* Function::operator() (Agent* agent, Table* params) {
	return exec (agent, params);
}

vector<string> Function::getParams (){
	lock_guard<mutex> lock(value_m);

	return parameters;
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
