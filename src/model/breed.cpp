#include "breed.h"

namespace stibbons {

Breed::Breed(WorldPtr world, FunctionPtr function) : world(world), function(function) {}

Breed::Breed(FunctionPtr function) : world(nullptr), function(function) {}

void Breed::addTurtle (TurtlePtr turtle) {
	lock_guard<recursive_mutex> lock(value_m);
	turtles.insert(turtle);
}

void Breed::removeTurtle (TurtlePtr turtle) throw(invalid_argument) {
	lock_guard<recursive_mutex> lock(value_m);
	if (turtles.find(turtle) == turtles.end())
		throw invalid_argument("This breed doesn't contain this turtle");

	turtles.erase(turtle);
}

unordered_set<TurtlePtr> Breed::getTurtles ( ) {
	lock_guard<recursive_mutex> lock(value_m);
	return unordered_set<TurtlePtr>(turtles);
}

TurtlePtr Breed::createTurtle () {
	TurtlePtr turtle = Turtle::construct(this);

	addTurtle(turtle);

	return turtle;
}

TurtlePtr Breed::createTurtle (AgentPtr parent) {
	TurtlePtr turtle = Turtle::construct(this, parent);

	addTurtle(turtle);

	return turtle;
}

WorldPtr Breed::getWorld () {
	lock_guard<recursive_mutex> lock(value_m);
	return world;
}

FunctionPtr Breed::getFunction () {
	lock_guard<recursive_mutex> lock(value_m);
	return function;
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
