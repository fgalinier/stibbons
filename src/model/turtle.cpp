#include "turtle.h"
#include "type.h"
#include "number.h"
#include "string.h"
#include "boolean.h"
#include "color.h"
#include <cmath>
#include <sstream>

#include "number.h"
#include "standard-function.h"

namespace stibbons {

error_code ec (errno,std::generic_category());

inline double radian (double degree) {
	return degree * M_PI / 180;
}

inline double degree (double radian) {
	return radian * 180 / M_PI;
}

Turtle::Turtle (Breed *breed) :
	Agent(breed ? dynamic_pointer_cast<Agent>(breed->getWorld()) : nullptr),
	id(breed ? breed->getWorld()->putTurtleId() : 0),
	breed(breed),
	angle(0.0),
	color(Color()),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>()){
}

Turtle::Turtle (Breed *breed, AgentPtr parent, turtle_id id) :
	Agent(parent),
	id(id),
	breed(breed),
	angle(0.0),
	color(Color()),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>()) {
		if (parent->getType() == Type::WORLD)
			setId(dynamic_pointer_cast<World>(parent)->putTurtleId());
		else setId(dynamic_pointer_cast<Turtle>(parent)->getWorld()->putTurtleId());
}

Turtle::Turtle (TurtlePtr parent) :
	Agent(parent),
	id(parent->getWorld()->putTurtleId()),
	breed(parent->breed),
	angle(parent->angle),
	color(parent->color),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>()) {
}

TurtlePtr Turtle::construct (Breed *breed) {
	auto self = shared_ptr<Turtle>(new Turtle(breed));
	self->init();

	return self;
}

TurtlePtr Turtle::construct (Breed *breed, AgentPtr parent, turtle_id id) {
	auto self = shared_ptr<Turtle>(new Turtle(breed, parent, id));
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

void Turtle::setProperty (string key, ValuePtr value) {
	lock_guard<recursive_mutex> lock(value_m);

	if (key == "distance_to")
		return;

	if (key == "face")
		return;

	if (key == "in_radius")
		return;

	if (key == "inbox")
		return;

	if (key == "teleport")
		return;

	if (key == "color") {
		if (value->getType() != Type::COLOR)
			return;

		auto val = dynamic_pointer_cast<Color>(value);
		setColor(*val);
		return;
	}

	if (key == "parent")
		return;

	if (key == "pos_x") {
		if (value->getType() != Type::NUMBER)
			return;

		auto val = dynamic_pointer_cast<Number>(value);
		auto pos = getPosition();
		pos.setValue(0, val->getValue());
		setPosition(pos);
		return;
	}

	if (key == "pos_y") {
		if (value->getType() != Type::NUMBER)
			return;

		auto val = dynamic_pointer_cast<Number>(value);
		auto pos = getPosition();
		pos.setValue(1, val->getValue());
		setPosition(pos);
		return;
	}

	if (key == "pos_angle") {
		if (value->getType() != Type::NUMBER)
			return;

		auto val = dynamic_pointer_cast<Number>(value);
		setAngle(val->getValue());
		return;
	}

	if (key == "world")
		return;

	if (key == "zone")
		return;

	Agent::setProperty(key, value);
}

ValuePtr Turtle::getProperty(string p) {
	lock_guard<recursive_mutex> lock(value_m);

	if (p == "distance_to")
		return DistanceToFunction::getInstance();

	if (p == "face")
		return FaceFunction::getInstance();

	if (p == "in_radius")
		return InRadiusFunction::getInstance();

	if (p == "inbox")
		return InboxFunction::getInstance();

	if (p == "teleport")
		return TeleportFunction::getInstance();

	if (p == "color")
		return make_shared<Color>(getColor());

	if (p == "parent")
		return getParent();

	if (p == "pos_x")
		return make_shared<Number>(getPosition().getValue(0));

	if (p == "pos_y")
		return make_shared<Number>(getPosition().getValue(1));

	if (p == "pos_angle")
		return make_shared<Number>(getAngle());

	if (p == "world")
		return getWorld();

	if (p == "zone")
		return getZone();

	return Agent::getProperty(p);
}

void Turtle::setId (turtle_id new_var) {
	lock_guard<recursive_mutex> lock(value_m);
	id=new_var;
}

Type Turtle::getType() const {
	return Type::TURTLE;
}

turtle_id Turtle::getId() {
	lock_guard<recursive_mutex> lock(value_m);
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

	return world->getZone(position);
}

void Turtle::setColor (Color color) {
	lock_guard<recursive_mutex> lock(value_m);
	this->color = color;

	if (line) {
		line = new Line(Point(position));
		line->setColor(getColor());
		getWorld()->addLine(line);
	}

	changed();
}

Color& Turtle::getColor () {
	lock_guard<recursive_mutex> lock(value_m);
	return color;
}

const Color& Turtle::getColor () const{
	return color;
}

void Turtle::setPosition(Point position) {
	lock_guard<recursive_mutex> lock(value_m);

	auto world = getWorld();
	bool warped = false;

	auto newPosition = Point(position);
	if (world) {
		auto size = world->getSize();
		warped = newPosition.warp(size, world->getWarp());
	}

	if (line)
		if (warped) {
			line->push_back(Point(position));

			line = new Line(Point(newPosition));
			line->setColor(getColor());
			world->addLine(line);
		}
		else
			line->push_back(Point(newPosition));

	this->position = newPosition;

	changed();
}

Point Turtle::getPosition() {
	lock_guard<recursive_mutex> lock(value_m);
	return position;
}

void Turtle::setAngle(double new_var) {
	lock_guard<recursive_mutex> lock(value_m);
	auto times = floor(new_var / 360.0);
	angle = new_var - (times * 360.0);
}

double Turtle::getAngle() {
	lock_guard<recursive_mutex> lock(value_m);
	return angle;
}

void Turtle::face(Point& point) {
	lock_guard<recursive_mutex> lock(value_m);

	auto world = getWorld();
	auto size = world->getSize();
	auto warp = world->getWarp();

	auto image = position.getClosestImage(point, size, warp);

	setAngle(degree(position.getAngleTo(image)));
}

double Turtle::getDistanceTo(Point& point) {
	lock_guard<recursive_mutex> lock(value_m);

	auto world = getWorld();
	auto size = world->getSize();
	auto warp = world->getWarp();

	auto image = position.getClosestImage(point, size, warp);

	return position.getDistanceTo(image);
}

void Turtle::forward(double dist) {
	double radians = radian(getAngle());

	double dx = cos(radians) * dist;
	double dy = sin(radians) * dist;

	auto newPosition = Point(position);
	newPosition.setValue(0, newPosition.getValue(0) + dx);
	newPosition.setValue(1, newPosition.getValue(1) + dy);
	setPosition(newPosition);

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

	line = new Line(Point(position));
	line->setColor(getColor());
	world->addLine(line);

	changed();
}

void Turtle::penUp() throw (future_error) {
	lock_guard<recursive_mutex> lock(value_m);
	auto world = getWorld();

	if (!world)
		return;

	if (!line)
		throw future_error(ec);

	line = nullptr;
}

TurtlePtr Turtle::createChild() {
	lock_guard<recursive_mutex> lock(value_m);
	auto child = Turtle::construct(dynamic_pointer_cast<Turtle>(shared_from_this()));

	breed->addTurtle (child);

	return child;
}

void Turtle::changed() {
	lock_guard<recursive_mutex> lock(value_m);
	auto world = getWorld();

	if (world)
		world->changed();
}

pair<TurtlePtr,ValuePtr> Turtle::getFirstMessage(){
	lock_guard<recursive_mutex> lock(value_m);
	auto result=messages.front();
	messages.pop_front();
	return result;
}

pair<TurtlePtr,ValuePtr> Turtle::getLastMessage(){
	lock_guard<recursive_mutex> lock(value_m);
	auto result=messages.back();
	messages.pop_back();
	return result;
}

void Turtle::send(TurtlePtr t, ValuePtr v){
	t->addMessage(dynamic_pointer_cast<Turtle>(shared_from_this()),v);
}

void Turtle::send(vector<TurtlePtr> t, ValuePtr v){
	for (auto tt : t)
	{
		tt->addMessage(dynamic_pointer_cast<Turtle>(shared_from_this()),v);
	}
}

void Turtle::sendAll(ValuePtr v){
	auto turtles=getWorld()->getTurtles();
	for (auto t : turtles)
		t->addMessage(dynamic_pointer_cast<Turtle>(shared_from_this()),v);
}

pair<TurtlePtr,ValuePtr> Turtle::recv(){
	return getFirstMessage();
}

size_t Turtle::checkMessage(){
	lock_guard<recursive_mutex> lock(value_m);
	return messages.size();
}

void Turtle::addMessage(TurtlePtr exp,ValuePtr v){
	lock_guard<recursive_mutex> lock(value_m);
    auto p=make_pair(exp,v);
	messages.push_back(p);
}

Object Turtle::exportTurtle(string name){

	Object synthese;
	Object s;

	if (!name.empty())
	{ s.push_back(Pair("Breed",name)); }

	s.push_back(Pair("color",this->getColor().toString()));
	s.push_back(Pair("angle",this->getAngle()));

	Point Tposition=getPosition();
	Array position;
	for (unsigned i=0;i<Tposition.getDimensions();i++)
		position.push_back(Tposition.getValue(i));
	s.push_back(Pair("position",position));
	
	exportProperties(&s);

	auto parent=getParent();
	if (parent->getType() == Type::WORLD)
	{
		s.push_back(Pair("parent","world"));
	}
	else s.push_back(Pair("parent", static_cast<uint64_t>(
		dynamic_pointer_cast<Turtle>(parent)->getId()
	)));

	string id=to_string(static_cast<uint64_t>(getId()));
	synthese.push_back(Pair(id,s));

	return synthese;
}

string Turtle::toString () {
	std::ostringstream oss;

	oss << "turtle(" << getId() << ")";

	return oss.str();
}

void Turtle::die () {
	lock_guard<recursive_mutex> lock(value_m);

	destroy();

	changed();
}

void Turtle::destroy () {
	lock_guard<recursive_mutex> lock(value_m);

	if (breed)
		breed->removeTurtle(dynamic_pointer_cast<Turtle>(shared_from_this()));

	Agent::destroy();
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
