#include "zone.h"

using namespace std;

namespace stibbons {

Zone::Zone (AgentPtr parent) : Agent(parent), color(Color(1.0, 1.0, 1.0)) {}

ZonePtr Zone::construct (AgentPtr parent) {
	auto self = shared_ptr<Zone>(new Zone (parent));
	self->init();

	return self;
}

void Zone::init () {
	Agent::init();
}

Zone::Zone(Zone& other) {
	lock_guard<mutex> lock(other.value_m);

	// Set this
	color = other.color;
}

Zone::Zone (Zone&& other) {
	lock_guard<mutex> lock(other.value_m);

	// Set this
	color = move(other.color);

	// Reset other
	other.color = Color();
}

Zone& Zone::operator= (Zone& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<mutex> self_lock(value_m, adopt_lock);
	lock_guard<mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	color = other.color;

	return *this;
}

Zone& Zone::operator= (Zone&& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<mutex> self_lock(value_m, adopt_lock);
	lock_guard<mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	color = move(other.color);

	// Reset other
	other.color = Color();

	return *this;
}

Type Zone::getType() const {
	return Type::ZONE;
}

void Zone::setColor (Color color) {
	{
		lock_guard<mutex> lock(value_m);
		this->color = color;
	}
	changed();
}

Color Zone::getColor () {
	lock_guard<mutex> lock(value_m);
	return color;
}

World* Zone::getWorld () {
	for (Agent *world = getParent() ; world != nullptr ; world = world->getParent())
		if (world->getType() == Type::WORLD)
			return dynamic_cast<World *>(world);

	return nullptr;
}

void Zone::changed() {
	lock_guard<mutex> lock(value_m);
	auto world = getWorld();

	if (world)
		world->changed();
}

string Zone::toString () {
	return "zone";
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
