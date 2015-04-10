#include "standard-function.h"

#include "nil.h"
#include "number.h"

#include <cstdlib>
#include <iostream>

using namespace std;

namespace stibbons {

Value* RandFunction::exec (Agent* agent, Table* params) {
	return new Number(rand());
}

PrintFunction::PrintFunction () : Function({"string"}) {}

Value* PrintFunction::exec (Agent* agent, Table* params) {
	cout << params->getValue("string")->toString();
	return &Nil::getInstance();
}

PrintlnFunction::PrintlnFunction () : Function({"string"}) {}

Value* PrintlnFunction::exec (Agent* agent, Table* params) {
	cout << params->getValue("string")->toString() << endl;
	return &Nil::getInstance();
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
