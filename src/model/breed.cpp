#include "breed.h"

namespace stibbons {

Breed::Breed(World *world, Function *function) : world(world), function(function) {}

Breed::Breed(Function *function) : world(nullptr), function(function) {}

Breed::~Breed () {
	for (auto turtle : turtles)
		delete turtle;

	delete function;
}

void Breed::addTurtle (Turtle *turtle) {
	turtles.insert(turtle);
}

void Breed::removeTurtle (Turtle *turtle) throw(invalid_argument) {
	if (turtles.find(turtle) == turtles.end())
		throw invalid_argument("This breed doesn't contain this turtle");

	turtles.erase(turtle);
}

unordered_set<Turtle*> Breed::getTurtles ( ) {
	return unordered_set<Turtle*>(turtles);
}

Turtle* Breed::createTurtle () {
	Turtle* turtle = new Turtle(this);

	addTurtle(turtle);

	return turtle;
}

Turtle* Breed::createTurtle (Turtle* parent) {
	Turtle* turtle = new Turtle(parent);

	addTurtle(turtle);

	return turtle;
}

void Breed::deleteTurtle (Turtle *turtle) throw(invalid_argument) {
	removeTurtle(turtle);

	delete turtle;
}

World *Breed::getWorld () {
	return world;
}

Function *Breed::getFunction () {
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
