#include "world.h"

#include "number.h"
#include "standard-function.h"

namespace stibbons {

World::World (Size worldSize, Size zoneSize, vector<bool> warp) throw(domain_error) : Agent(nullptr), worldSize(worldSize), zoneSize(zoneSize), warp(warp), id(0) {
	if (worldSize.getDimensions() != zoneSize.getDimensions())
		throw domain_error("Can't create a world with a dimension number different to its zones'");

	if (worldSize.getDimensions() != warp.size())
		throw domain_error("Can't create a world without a different number of warping values than there is dimensions");

	for (size_t i = 0 ; i < getDimensions() ; i++)
		size.setValue(i, worldSize.getValue(i) * zoneSize.getValue(i));

}

WorldPtr World::construct (Size worldSize, Size zoneSize, vector<bool> warp) throw(domain_error) {
	auto self = shared_ptr<World>(new World (worldSize, zoneSize, warp));
	self->init();

	return self;
}

void World::init () {
	Agent::init();

	// Set the default colors
	initColors();

	// Count the number of zones
	size_t zonesNb = worldSize.getDimensions() > 0 ? 1 : 0;

	for (size_t i = 0 ; i < worldSize.getDimensions() ; i++) {
		zonesNb *= worldSize.getValue(i);
	}

	// Create the zones
	for (size_t i = 0 ; i < zonesNb ; i++) {
		auto zone = Zone::construct(shared_from_this());
		zones.push_back(zone);
	}

	// General purpose standard functions
	setProperty("print", PrintFunction::getInstance());
	setProperty("println", PrintlnFunction::getInstance());
	setProperty("rand", RandFunction::getInstance());
}

World::~World () {
	for (auto i : lines)
		delete i;
}

Type World::getType() const {
	return Type::WORLD;
}

void World::setProperty (string key, ValuePtr value) {
	lock_guard<recursive_mutex> lock(value_m);

	if (key == "max-x")
		return;

	if (key == "max-y")
		return;

	Agent::setProperty(key, value);
}

ValuePtr World::getProperty(string p) {
	lock_guard<recursive_mutex> lock(value_m);

	if (p == "max-x")
		return make_shared<Number>(worldSize.getValue(0) *
		                           zoneSize.getValue(0));

	if (p == "max-y")
		return make_shared<Number>(worldSize.getValue(1) *
		                           zoneSize.getValue(1));

	return Agent::getProperty(p);
}

void World::addLine (Line* add_object) {
	lock_guard<recursive_mutex> lock(value_m);

	lines.push_back(add_object);

	//changed();
}

vector<Line *> World::getLines () {
	lock_guard<recursive_mutex> lock(value_m);

	return lines;
}

vector<Line> World::getLinesSince (vector<size_t>& sizes) {
	lock_guard<recursive_mutex> lock(value_m);

	auto newLines = vector<Line>();

	size_t actualSize = lines.size();
	size_t previousSize = sizes.size();

	for (size_t i = 0 ; i < actualSize ; i++) {
		size_t startPoint = lines[i]->size() - 1;
		size_t previousStartPoint = (i >= previousSize) ? 0 : sizes[i];

		newLines.push_back(Line(*lines[i], previousStartPoint));

		if (i >= previousSize)
			sizes.push_back(startPoint);
		else
			sizes[i] = startPoint;
	}

	return newLines;
}

BreedPtr World::getBreed (string name) throw(out_of_range) {
	lock_guard<recursive_mutex> lock(value_m);

	auto breed_i = namedBreeds.find(name);

	if (breed_i == namedBreeds.end())
		throw out_of_range("There is no breed with this name");

	return breed_i->second;
}

unordered_set<TurtlePtr> World::getTurtles () {
	lock_guard<recursive_mutex> lock(value_m);

	auto turtles = unordered_set<TurtlePtr>();

	for (auto breed : namedBreeds)
		for (auto turtle : (breed.second)->getTurtles())
			turtles.insert(turtle);

	for (auto breed : anonymousBreeds)
		for (auto turtle : breed->getTurtles())
			turtles.insert(turtle);

	return turtles;
}

ZonePtr World::getZone (Size& coordinates) throw(domain_error) {
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

ZonePtr World::getZone (Point& point) throw(domain_error) {
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

Size World::getSize () {
	return Size(size);
}

Size World::getWorldSize () {
	return Size(worldSize);
}

Size World::getZoneSize () {
	return Size(zoneSize);
}

vector<bool> World::getWarp () {
	return warp;
}

BreedPtr World::createBreed (FunctionPtr function, string name) throw(invalid_argument) {
	if (namedBreeds.find(name) != namedBreeds.end())
		throw invalid_argument("Can't create a breed with an already used name");

	auto breed = shared_ptr<Breed>(new Breed(dynamic_pointer_cast<World>(shared_from_this()), function));

	lock_guard<recursive_mutex> lock(value_m);

	namedBreeds.insert({{name, breed}});

	return breed;
}

BreedPtr World::createBreed (FunctionPtr function) {
	auto breed = shared_ptr<Breed>(new Breed(dynamic_pointer_cast<World>(shared_from_this()), function));

	lock_guard<recursive_mutex> lock(value_m);

	anonymousBreeds.insert(breed);

	return breed;
}

string World::toString () {
	return "world";
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


