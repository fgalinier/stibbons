#include "standard-function.h"

#include "nil.h"
#include "number.h"
#include "turtle.h"

#include <cstdlib>
#include <iostream>
#include <thread>

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

ValuePtr TeleportFunction::exec (AgentPtr agent, TablePtr params) {
	auto x = params->getValue("x");
	auto y = params->getValue("y");
	auto angle = params->getValue("angle");

	auto turtle = dynamic_pointer_cast<Turtle>(agent);

	turtle->setValue(0, dynamic_pointer_cast<Number>(x)->getValue());
	turtle->setValue(1, dynamic_pointer_cast<Number>(y)->getValue());
	turtle->setAngle(dynamic_pointer_cast<Number>(angle)->getValue());

	return make_shared<Nil>();
}

SendFunction::SendFunction () : Function({"recipient", "message"}) {}

ValuePtr SendFunction::exec (AgentPtr agent, TablePtr params) {
	auto recipient = params->getValue("recipient");
	auto message = params->getValue("message");

	auto turtle = dynamic_pointer_cast<Turtle>(agent);

	turtle->send(dynamic_pointer_cast<Turtle>(recipient), message);

	return make_shared<Nil>();
}

SendAllFunction::SendAllFunction () : Function({"message"}) {}

ValuePtr SendAllFunction::exec (AgentPtr agent, TablePtr params) {
	auto message = params->getValue("message");

	auto turtle = dynamic_pointer_cast<Turtle>(agent);

	turtle->sendAll(message);

	return make_shared<Nil>();
}

ValuePtr RecvFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = dynamic_pointer_cast<Turtle>(agent);

	while (turtle->checkMessage() <= 0)
		this_thread::sleep_for(chrono::milliseconds(10));

	return turtle->recv().second;
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
