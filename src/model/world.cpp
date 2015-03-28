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
	lock_guard<mutex> lock(value_m);

	lines.push_back(add_object);

	changed();
}

vector<Line *> World::getLines () {
	lock_guard<mutex> lock(value_m);

	return lines;
}

void World::addTurtle (Turtle * add_object) {
	lock_guard<mutex> lock(value_m);

	turtles.push_back(add_object);

	add_object->onChanged([this]() {
		changed();
	});
	changed();
}

void World::removeTurtle (Turtle *turtle) {
	lock_guard<mutex> lock(value_m);

	for (auto i = turtles.begin(); i != turtles.end() ; i++) {
		if(*i == turtle) {
			turtles.erase(i);
			delete turtle;
			return;
		}
	}

	changed();
}

vector<Turtle *> World::getTurtles () {
	lock_guard<mutex> lock(value_m);

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


