#include "turtle.h"

#include <cmath>
#include <sstream>

#include "standard-function.h"

namespace stibbons {

error_code ec (errno,std::generic_category());

/**
 * Check whether a value is between 0 and 1 and put it truncated to fit
 * in these boundaries.
 */
inline double radian (double degree) {
	return degree * M_PI / 180;
}

Turtle::Turtle () :
	Agent(nullptr),
	id(0),
	breed(nullptr),
	angle(0.0),
	color(Color()),
	line(nullptr) {
		initAttributes();
	}

Turtle::Turtle (AgentPtr parent, turtle_id id) :
	Agent(parent),
	id(id),
	breed(nullptr),
	angle(0.0),
	color(Color()),
	line(nullptr) {
		initAttributes();
	}

Turtle::Turtle (Breed *breed) :
	Agent(dynamic_pointer_cast<Agent>(breed->getWorld())),
	id(0),
	breed(breed),
	angle(0.0),
	color(Color()),
	line(nullptr) {
		initAttributes();
	}

Turtle::Turtle (TurtlePtr parent) :
	Agent(parent),
	id(0),
	breed(parent->breed),
	angle(parent->angle),
	color(parent->color),
	line(nullptr) {
		initAttributes();
	}

void Turtle::initAttributes () {
	setProperty(pair<string,ValuePtr>("teleport", make_shared<TeleportFunction>()));
}

TurtlePtr Turtle::construct () {
	auto self = shared_ptr<Turtle>(new Turtle());
	self->init();

	return self;
}

TurtlePtr Turtle::construct (AgentPtr parent, turtle_id id) {
	auto self = shared_ptr<Turtle>(new Turtle(parent, id));
	self->init();

	return self;
}

TurtlePtr Turtle::construct (Breed *breed) {
	auto self = shared_ptr<Turtle>(new Turtle(breed));
	self->init();

	return self;
}

TurtlePtr Turtle::construct (TurtlePtr parent) {
	auto self = shared_ptr<Turtle>(new Turtle(parent));
	self->init();

	return self;
}

void Turtle::init () {
	Agent::init();
}

void Turtle::setId (turtle_id new_var) {
	lock_guard<mutex> lock(value_m);
	id=new_var;
}

Type Turtle::getType() const {
	return Type::TURTLE;
}

turtle_id Turtle::getId() {
	lock_guard<mutex> lock(value_m);
	return id;
}

WorldPtr Turtle::getWorld () {
	if (breed)
		return breed->getWorld();

	for (AgentPtr world = getParent() ; world != nullptr ; world = world->getParent())
		if (world->getType() == Type::WORLD)
			return dynamic_pointer_cast<World>(world);

	return nullptr;
}

ZonePtr Turtle::getZone () {
	auto world = getWorld();

	if (world == nullptr)
		return nullptr;

	return world->getZone(*this);
}

void Turtle::setColor (Color color) {
	lock_guard<mutex> lock(value_m);
	this->color = color;
}

Color& Turtle::getColor () {
	lock_guard<mutex> lock(value_m);
	return color;
}

const Color& Turtle::getColor () const{
	return color;
}

void Turtle::setAngle(double new_var) {
	lock_guard<mutex> lock(value_m);
	auto times = floor(new_var / 360.0);
	angle = new_var - (times * 360.0);
}

double Turtle::getAngle() {
	lock_guard<mutex> lock(value_m);
	return angle;
}

void Turtle::forward(double dist) {
	double radians = radian(getAngle());

	double dx = cos(radians) * dist;
	double dy = sin(radians) * dist;

	setValue(0, getValue(0) + dx);
	setValue(1, getValue(1) + dy);

	if (line)
		line->push_back(Point(*this));

	changed();
}

void Turtle::turnRight(double angle) {
	setAngle(getAngle() + angle);
	changed();
}

void Turtle::turnLeft(double angle) {
	setAngle(getAngle() - angle);
	changed();
}

void Turtle::penDown() throw (future_error) {
	auto world = getWorld();

	if (!world)
		return;

	if (line)
		throw future_error(ec);

	line = new Line();
	line->setColor(getColor());
	world->addLine(line);
	line->push_back(Point(*this));

	changed();
}

void Turtle::penUp() throw (future_error) {
	lock_guard<mutex> lock(value_m);
	auto world = getWorld();

	if (!world)
		return;

	if (!line)
		throw future_error(ec);

	line = nullptr;
}

TurtlePtr Turtle::createChild() {
	lock_guard<mutex> lock(value_m);
	auto child = Turtle::construct(shared_from_this());

	breed->addTurtle (child);

	return child;
}

void Turtle::changed() {
	lock_guard<mutex> lock(value_m);
	auto world = getWorld();

	if (world)
		world->changed();
}

string Turtle::toString () {
	std::ostringstream oss;

	oss << "turtle(" << getId() << ")";

	return oss.str();
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
