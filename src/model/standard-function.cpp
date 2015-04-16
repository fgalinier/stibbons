#include "standard-function.h"

#include "nil.h"
#include "number.h"
#include "turtle.h"

#include <cstdlib>
#include <iostream>

using namespace std;

namespace stibbons {

ValuePtr RandFunction::exec (AgentPtr agent, TablePtr params) {
	return make_shared<Number>(rand());
}

PrintFunction::PrintFunction () : Function({"string"}) {}

ValuePtr PrintFunction::exec (AgentPtr agent, TablePtr params) {
	cout << params->getValue("string")->toString();
	return make_shared<Nil>();
}

PrintlnFunction::PrintlnFunction () : Function({"string"}) {}

ValuePtr PrintlnFunction::exec (AgentPtr agent, TablePtr params) {
	cout << params->getValue("string")->toString() << endl;
	return make_shared<Nil>();
}

TeleportFunction::TeleportFunction () : Function({"x", "y", "angle"}) {}

Value* TeleportFunction::exec (Agent* agent, Table* params) {
	auto x = params->getValue("x");
	auto y = params->getValue("y");
	auto angle = params->getValue("angle");

	auto turtle = dynamic_cast<Turtle*>(agent);

	turtle->setValue(0, dynamic_cast<Number*>(x)->getValue());
	turtle->setValue(1, dynamic_cast<Number*>(y)->getValue());
	turtle->setAngle(dynamic_cast<Number*>(angle)->getValue());

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