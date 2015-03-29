#include "breed.h"

namespace stibbons {

Breed::Breed(World *world, Function *function) : world(world), function(function) {}

Breed::Breed(Function *function) : world(nullptr), function(function) {}

void Breed::addTurtles ( Turtle * add_object ) {
	turtles.push_back(add_object);
}

void Breed::removeTurtles ( Turtle * remove_object ) {
	int i, size = turtles.size();
	for ( i = 0; i < size; ++i) {
	Turtle * item = turtles.at(i);
	if(item == remove_object) {
		vector<Turtle *>::iterator it = turtles.begin() + i;
		turtles.erase(it);
		return;
	}
	}
}
vector<Turtle *> Breed::getTurtlesList ( ) {
	return turtles;
}

Turtle* Breed::createTurtle () {
	Turtle* turtle = new Turtle(this, getWorld());

	turtles.push_back(turtle);

	return turtle;
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
