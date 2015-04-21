#include "turtle.h"
#include "type.h"

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

Turtle::Turtle () :
	Agent(nullptr),
	id(0),
	breed(nullptr),
	angle(0.0),
	color(Color()),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>()){
		initAttributes();
	}

Turtle::Turtle (AgentPtr parent, turtle_id id) :
	Agent(parent),
	id(id),
	breed(nullptr),
	angle(0.0),
	color(Color()),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>()) {
		initAttributes();
	}

Turtle::Turtle (Breed *breed) :
	Agent(dynamic_pointer_cast<Agent>(breed->getWorld())),
	id(0),
	breed(breed),
	angle(0.0),
	color(Color()),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>()) {
		initAttributes();
	}

Turtle::Turtle (TurtlePtr parent) :
	Agent(parent),
	id(0),
	breed(parent->breed),
	angle(parent->angle),
	color(parent->color),
	line(nullptr),
	messages(deque<pair<TurtlePtr,ValuePtr>>())  {
		initAttributes();
	}

void Turtle::initAttributes () {
	// Set the default colors
	initColors();

	// General purpose standard functions
	setProperty("print", PrintFunction::getInstance());
	setProperty("println", PrintlnFunction::getInstance());
	setProperty("rand", RandFunction::getInstance());

	// Turtle specific standard functions
	setProperty("distance-to", DistanceToFunction::getInstance());
	setProperty("face", FaceFunction::getInstance());
	setProperty("in-radius", InRadiusFunction::getInstance());
	setProperty("inbox", InboxFunction::getInstance());
	setProperty("recv", RecvFunction::getInstance());
	setProperty("send", SendFunction::getInstance());
	setProperty("send-all", SendAllFunction::getInstance());
	setProperty("teleport", TeleportFunction::getInstance());
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

void Turtle::setProperty (string key, ValuePtr value) {
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

	if (key == "pos-x") {
		if (value->getType() != Type::NUMBER)
			return;

		auto val = dynamic_pointer_cast<Number>(value);
		auto pos = getPosition();
		pos.setValue(0, val->getValue());
		setPosition(pos);
		return;
	}

	if (key == "pos-y") {
		if (value->getType() != Type::NUMBER)
			return;

		auto val = dynamic_pointer_cast<Number>(value);
		auto pos = getPosition();
		pos.setValue(1, val->getValue());
		setPosition(pos);
		return;
	}

	if (key == "pos-angle") {
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

	if (p == "color")
		return make_shared<Color>(getColor());

	if (p == "parent")
		return getParent();

	if (p == "pos-x")
		return make_shared<Number>(getPosition().getValue(0));

	if (p == "pos-y")
		return make_shared<Number>(getPosition().getValue(1));

	if (p == "pos-angle")
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
	auto child = Turtle::construct(shared_from_this());

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

Object Turtle::exportTurtle(){
	Object synthese;
	synthese.push_back(Pair("id",getId()));
	synthese.push_back(Pair("color",this->getColor().toString()));
/*
	unordered_map<string,ValuePtr>* properties=getProperty();
	for (auto m : *properties)
	{
		if (m.second->getType() == Type::COLOR)
			synthese.push_back(Pair(m.first,dynamic_pointer_cast<Color>(m.second)->toString()));
	}
*/
	exportProperties(synthese);
	auto parent=getParent();
	if (parent->getType() == Type::WORLD)
	{
		synthese.push_back(Pair("parent","world"));
	}
	else synthese.push_back(Pair("parent",dynamic_pointer_cast<Turtle>(parent)->getId()));

	return synthese;
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
