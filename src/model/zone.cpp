#include "zone.h"

using namespace std;

namespace stibbons {

Zone::Zone (AgentPtr parent) : Agent(parent), color(Color(1.0, 1.0, 1.0)),id(dynamic_pointer_cast<World>(parent)->putZoneId()) {}

ZonePtr Zone::construct (AgentPtr parent) {
	auto self = shared_ptr<Zone>(new Zone (parent));
	self->init();

	return self;
}

void Zone::init () {
	Agent::init();
}

Zone::Zone(Zone& other) {
	lock_guard<recursive_mutex> lock(other.value_m);

	// Set this
	color = other.color;
}

Zone::Zone (Zone&& other) {
	lock_guard<recursive_mutex> lock(other.value_m);

	// Set this
	color = move(other.color);

	// Reset other
	other.color = Color();
}

Zone& Zone::operator= (Zone& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
	lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	color = other.color;

	return *this;
}

Zone& Zone::operator= (Zone&& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
	lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	color = move(other.color);

	// Reset other
	other.color = Color();

	return *this;
}

Type Zone::getType() const {
	return Type::ZONE;
}

void Zone::setProperty (string key, ValuePtr value) {
	lock_guard<recursive_mutex> lock(value_m);

	if (key == "color") {
		if (value->getType() != Type::COLOR)
			return;

		auto val = dynamic_pointer_cast<Color>(value);
		setColor(*val);
		return;
	}

	if (key == "parent")
		return;

	if (key == "world")
		return;

	Agent::setProperty(key, value);
}

ValuePtr Zone::getProperty(string p) {
	lock_guard<recursive_mutex> lock(value_m);

	if (p == "color")
		return make_shared<Color>(getColor());

	if (p == "parent")
		return getParent();

	if (p == "world")
		return getWorld();

	return Agent::getProperty(p);
}

void Zone::setColor (Color color) {
	{
		lock_guard<recursive_mutex> lock(value_m);
		this->color = color;
	}
	changed();
}

Color Zone::getColor () {
	lock_guard<recursive_mutex> lock(value_m);
	return color;
}

WorldPtr Zone::getWorld () {
	for (AgentPtr world = getParent() ; world != nullptr ; world = world->getParent())
		if (world->getType() == Type::WORLD)
			return dynamic_pointer_cast<World>(world);

	return nullptr;
}

zone_id Zone::getId (){
	lock_guard<recursive_mutex> lock(value_m);
	return id;
}

void Zone::setId (zone_id z){
	 id=z;
}

void Zone::changed() {
	lock_guard<recursive_mutex> lock(value_m);
	auto world = getWorld();

	if (world)
		world->changed();
}

string Zone::toString () {
	return "zone";
}

Object Zone::exportZone() {
	Object synthese;
	Object s;

	s.push_back(Pair("color",this->getColor().toString()));
	exportProperties(&s);

	string id=to_string(static_cast<uint64_t>(getId()));
	synthese.push_back(Pair(id,s));
	return synthese;
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
