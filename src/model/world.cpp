#include "world.h"

namespace stibbons {

World::World (unsigned width, unsigned height) :
	width(width),
	height(height),
	zones(vector<Zone*>()),
	lines(vector<Line*>()),
	turtles(vector<Turtle*>()),
	id(0) {
	for (unsigned i = 0 ; i < width * height ; i++)
		zones.push_back(new Zone());
}

World::~World () {
	for (auto i : zones)
		delete i;

	for (auto i : lines)
		delete i;

	for (auto i : turtles)
		delete i;
}

void World::addLine (Line* add_object) {
	lines.push_back(add_object);
}

vector<Line *> World::getLines () {
	return lines;
}

void World::addTurtle (Turtle * add_object) {
	turtles.push_back(add_object);
}

void World::removeTurtle (Turtle *turtle) {
	for (auto i = turtles.begin(); i != turtles.end() ; i++) {
		if(*i == turtle) {
			turtles.erase(i);
			delete turtle;
			return;
		}
	}
}

vector<Turtle *> World::getTurtles () {
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


