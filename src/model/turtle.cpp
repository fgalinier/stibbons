#include "turtle.h"

#include <cmath>

namespace stibbons {

error_code ec (errno,std::generic_category());

/**
 * Check whether a value is between 0 and 1 and put it truncated to fit
 * in these boundaries.
 */
inline double radian (double degree) {
	return degree * M_PI / 180;
}

Turtle::Turtle (Agent* parent, turtle_id id) : Agent(parent), id(id), breed(nullptr), angle(0.0), color(Color()), line(nullptr) {}

Turtle::Turtle (Breed *breed, Agent *parent) : Agent(parent), id(0), breed(breed), angle(0.0), color(Color()), line(nullptr) {}

void Turtle::setId (turtle_id new_var) {
	id=new_var;
}

Type Turtle::getType() const {
	return Type::TURTLE;
}

turtle_id Turtle::getId() const {
	return id;
}

World* Turtle::getWorld () {
	if (breed)
		return breed->getWorld();

	for (Agent *world = getParent() ; world != nullptr ; world = world->getParent())
		if (world->getType() == Type::WORLD)
			return dynamic_cast<World *>(world);

	return nullptr;
}

void Turtle::setColor (Color color) {
	this->color = color;

	changed();
}

Color& Turtle::getColor () {
	return color;
}

const Color& Turtle::getColor () const {
	return color;
}

void Turtle::setAngle(double new_var) {
	auto times = floor(new_var / 360.0);
	angle = new_var - (times * 360.0);

	changed();
}

double Turtle::getAngle() {
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
}

void Turtle::turnLeft(double angle) {
	setAngle(getAngle() - angle);
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
	auto world = getWorld();

	if (!world)
		return;

	if (!line)
		throw future_error(ec);

	line = nullptr;
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
