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

inline WorldPtr asWorld (AgentPtr agent) throw(domain_error) {
	auto world = dynamic_pointer_cast<World>(agent);
	if (!world)
		throw domain_error("The agent is expected to be of type " + toString(Type::WORLD));
	return world;
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

inline FunctionPtr asFunction (ValuePtr value, string param) throw(domain_error) {
	auto casted = dynamic_pointer_cast<Function>(value);
	if (!casted)
		paramError (param, Type::FUNCTION);
	return casted;
}

inline TurtlePtr asTurtle (ValuePtr value, string param) throw(domain_error) {
	auto casted = dynamic_pointer_cast<Turtle>(value);
	if (!casted)
		paramError (param, Type::TURTLE);
	return casted;
}

inline TablePtr asTable (ValuePtr value, string param) throw(domain_error) {
	auto casted = dynamic_pointer_cast<Table>(value);
	if (!casted)
		paramError (param, Type::TABLE);
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

RandomFunction::RandomFunction () : Function({"min", "max"}) {}

ValuePtr RandomFunction::exec (AgentPtr agent, TablePtr params) {
	auto min = long(asNumber(params->getValue("min"), "min")->getValue());
	auto max = long(asNumber(params->getValue("max"), "max")->getValue());
	max = max - min;
	auto res = rand() % max + min;
	
	return make_shared<Number>(res);
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
		if (turtle->getDistanceTo(point) <= d && other != turtle)
			turtles->append(other);
	}

	return turtles;
}

AskZonesFunction::AskZonesFunction () : Function({"function"}) {}

ValuePtr AskZonesFunction::exec (AgentPtr agent, TablePtr params) {
	auto world = asWorld(agent);

	auto function = asFunction(params->getValue("function"), "function");

	auto ws = world->getSize();
	auto is = Size(2);

	auto newParams = make_shared<Table>();

	for (is.setValue(0, 0) ;
	     is.getValue(0) < ws.getValue(0) ;
	     is.setValue(0, is.getValue(0) + 1))
	for (is.setValue(1, 0) ;
	     is.getValue(1) < ws.getValue(1) ;
	     is.setValue(1, is.getValue(1) + 1)) {
		auto zone = world->getZone(is);
		if (zone) {
			function->exec(zone, newParams);
		}
	}

	return Nil::getInstance();
}

SizeFunction::SizeFunction () : Function({"table"}) {}

ValuePtr SizeFunction::exec (AgentPtr agent, TablePtr params) {
	auto table = asTable(params->getValue("table"), "table");

	auto size = table->length();

	return make_shared<Number>(size);
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
