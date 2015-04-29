#include "standard-function.h"

#include "math.h"
#include "nil.h"
#include "number.h"
#include "turtle.h"
#include "type-value.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

namespace stibbons {

inline void paramError (string name, Type expected) throw(domain_error) {
	throw domain_error("Parameter " + name + " is expected to be of type " + toString(expected));
}

inline TurtlePtr asTurtle (AgentPtr agent) throw(domain_error) {
	auto turtle = dynamic_pointer_cast<Turtle>(agent);
	if (!turtle)
		throw domain_error("The agent is expected to be of type " + toString(Type::TURTLE));
	return turtle;
}

inline NumberPtr asNumber (ValuePtr value, string param) throw(domain_error) {
	auto casted = dynamic_pointer_cast<Number>(value);
	if (!casted)
		paramError (param, Type::NUMBER);
	return casted;
}

inline TurtlePtr asTurtle (ValuePtr value, string param) throw(domain_error) {
	auto casted = dynamic_pointer_cast<Turtle>(value);
	if (!casted)
		paramError (param, Type::TURTLE);
	return casted;
}

TypeOfFunction::TypeOfFunction () : Function({"value"}) {}

ValuePtr TypeOfFunction::exec (AgentPtr agent, TablePtr params) {
	Type type = params->getValue("value")->getType();
	return make_shared<TypeValue>(type);
}

ValuePtr RandFunction::exec (AgentPtr agent, TablePtr params) {
	return make_shared<Number>(rand());
}

PrintFunction::PrintFunction () : Function({"value"}) {}

ValuePtr PrintFunction::exec (AgentPtr agent, TablePtr params) {
	cout << params->getValue("value")->toString();
	return Nil::getInstance();
}

PrintlnFunction::PrintlnFunction () : Function({"value"}) {}

ValuePtr PrintlnFunction::exec (AgentPtr agent, TablePtr params) {
	std::ostringstream oss;
	oss << params->getValue("value")->toString() << endl;
	cout << oss.str();
	return Nil::getInstance();
}

TeleportFunction::TeleportFunction () : Function({"x", "y", "angle"}) {}

ValuePtr TeleportFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	auto x = asNumber(params->getValue("x"), "x")->getValue();
	auto y = asNumber(params->getValue("y"), "y")->getValue();
	auto angle = asNumber(params->getValue("angle"), "angle")->getValue();

	auto position = Point(2);
	position.setValue(0, x);
	position.setValue(1, y);

	turtle->setPosition(position);
	turtle->setAngle(angle);

	return Nil::getInstance();
}

SendFunction::SendFunction () : Function({"recipient", "message"}) {}

ValuePtr SendFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	auto recipient = asTurtle(params->getValue("recipient"), "recipient");
	auto message = params->getValue("message");

	turtle->send(recipient, message);

	return Nil::getInstance();
}

SendAllFunction::SendAllFunction () : Function({"message"}) {}

ValuePtr SendAllFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	auto message = params->getValue("message");

	turtle->sendAll(message);

	return Nil::getInstance();
}

ValuePtr RecvFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	while (turtle->checkMessage() <= 0)
		this_thread::sleep_for(chrono::milliseconds(10));

	return turtle->recv().second;
}

ValuePtr InboxFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	return make_shared<Number>(turtle->checkMessage());
}

DistanceToFunction::DistanceToFunction () : Function({"turtle"}) {}

ValuePtr DistanceToFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	auto other = asTurtle(params->getValue("turtle"), "turtle");

	auto point = other->getPosition();
	auto d = turtle->getDistanceTo(point);

	return make_shared<Number>(d);
}

FaceFunction::FaceFunction () : Function({"turtle"}) {}

ValuePtr FaceFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	auto other = asTurtle(params->getValue("turtle"), "turtle");

	auto point = other->getPosition();
	turtle->face(point);

	return Nil::getInstance();
}

InRadiusFunction::InRadiusFunction () : Function({"distance"}) {}

ValuePtr InRadiusFunction::exec (AgentPtr agent, TablePtr params) {
	auto turtle = asTurtle(agent);

	auto distance = asNumber(params->getValue("distance"), "distance");

	double d = distance->getValue();

	auto turtles = make_shared<Table>();

	for (auto other : turtle->getWorld()->getTurtles()) {
		auto point = other->getPosition();
		if (turtle->getDistanceTo(point) <= d)
			turtles->append(other);
	}

	return turtles;
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
