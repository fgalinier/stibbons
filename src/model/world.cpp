#include "world.h"

namespace stibbons {

World::World (Size worldSize, Size zoneSize) throw(domain_error) : Agent(nullptr), worldSize(worldSize), zoneSize(zoneSize), id(0) {
	if (worldSize.getDimensions() != zoneSize.getDimensions())
		throw domain_error("Can't create a world with a dimension number different to its zones'");

	// Count the number of zones
	size_t zonesNb = worldSize.getDimensions() > 0 ? 1 : 0;

	for (size_t i = 0 ; i < worldSize.getDimensions() ; i++) {
		zonesNb *= worldSize.getValue(i);
	}

	// Create the zones
	for (size_t i = 0 ; i < zonesNb ; i++) {
		auto zone = new Zone(this);
		zones.push_back(zone);
	}

	// Set default colors
	setProperty(pair<string,Value*>("black", new Color(0.0, 0.0, 0.0)));
	setProperty(pair<string,Value*>("white", new Color(1.0, 1.0, 1.0)));

	setProperty(pair<string,Value*>("grey", new Color(0.5, 0.5, 0.5)));

	setProperty(pair<string,Value*>("red", new Color(1.0, 0.0, 0.0)));
	setProperty(pair<string,Value*>("green", new Color(0.0, 1.0, 0.0)));
	setProperty(pair<string,Value*>("blue", new Color(0.0, 0.0, 1.0)));

	setProperty(pair<string,Value*>("yellow", new Color(1.0, 1.0, 0.0)));
	setProperty(pair<string,Value*>("cyan", new Color(0.0, 1.0, 1.0)));
	setProperty(pair<string,Value*>("magenta", new Color(1.0, 0.0, 1.0)));
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

	//changed();
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

Zone* World::getZone (Size& coordinates) throw(domain_error) {
	// If a point of different dimension number is passed, it's an error
	if (worldSize.getDimensions() != coordinates.getDimensions())
		throw domain_error("Can't get a zone for coordinates in a dimension different from the world's");

	// If no zone correspond to the coordinates, return a null pointer
	for (size_t i = 0 ; i < coordinates.getDimensions() ; i++)
		if (coordinates.getValue(i) > worldSize.getValue(i))
			return nullptr;

	// Compute the index of the zone
	size_t prevDimensionsSize = 1;
	size_t index = 0;
	for (size_t i = 0 ; i < coordinates.getDimensions() ; i++) {
		index += coordinates.getValue(i) * prevDimensionsSize;
		prevDimensionsSize *= worldSize.getValue(i);
	}

	return zones[index];
}

Zone* World::getZone (Point& point) throw(domain_error) {
	// If a point of different dimension number is passed, it's an error
	if (worldSize.getDimensions() != point.getDimensions())
		throw domain_error("Can't get a zone for a point which dimension is different from the world's");

	// Compute the coordinates of the requested zone
	auto requestedZone = Size(point.getDimensions());
	for (size_t i = 0 ; i < requestedZone.getDimensions() ; i++)
		requestedZone.setValue(i, (size_t) (point.getValue(i) / zoneSize.getValue(i)));

	return getZone(requestedZone);
}

unsigned World::getDimensions () const {
	return worldSize.getDimensions();
}

Size World::getWorldSize () {
	return Size(worldSize);
}

Size World::getZoneSize () {
	return Size(zoneSize);
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


