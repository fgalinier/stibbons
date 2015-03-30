#include "world.h"

namespace stibbons {

World::World (Agent *parent, unsigned width, unsigned height) :
	Agent(parent),
	width(width),
	height(height),
	zones(vector<Zone*>()),
	lines(vector<Line*>()),
	namedBreeds(unordered_map<string,Breed*>()),
	anonymousBreeds(unordered_set<Breed*>()),
	id(0) {
	for (unsigned i = 0 ; i < width * height ; i++) {
		auto zone = new Zone(this);
		zones.push_back(zone);
	}
}

World::~World () {
	for (auto i : zones)
		delete i;

	for (auto i : lines)
		delete i;

	for (auto i : anonymousBreeds)
		delete i;

	for (auto i : namedBreeds)
		delete i.second;
}

Type World::getType() const {
	return Type::WORLD;
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

Breed* World::getBreed (string name) throw(out_of_range) {
	lock_guard<mutex> lock(value_m);

	auto breed_i = namedBreeds.find(name);

	if (breed_i == namedBreeds.end())
		throw out_of_range("There is no breed with this name");

	return breed_i->second;
}

unordered_set<Turtle *> World::getTurtles () {
	lock_guard<mutex> lock(value_m);

	auto turtles = unordered_set<Turtle *>();

	for (auto breed : namedBreeds)
		for (auto turtle : (breed.second)->getTurtles())
			turtles.insert(turtle);

	for (auto breed : anonymousBreeds)
		for (auto turtle : breed->getTurtles())
			turtles.insert(turtle);

	return turtles;
}

Breed* World::createBreed (Function& function, string name) throw(invalid_argument) {
	if (namedBreeds.find(name) != namedBreeds.end())
		throw invalid_argument("Can't create a breed with an already used name");

	Breed* breed = new Breed(this, &function);

	lock_guard<mutex> lock(value_m);

	namedBreeds.insert({{name, breed}});

	return breed;
}

Breed* World::createBreed (Function& function) {
	Breed* breed = new Breed(this, &function);

	lock_guard<mutex> lock(value_m);

	anonymousBreeds.insert(breed);

	return breed;
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


