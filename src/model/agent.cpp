#include "agent.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

#include "standard-function.h"

#include <cmath>

namespace stibbons {

Agent::Agent (AgentPtr parent) : parent(parent) {
	properties=new unordered_map<string,ValuePtr>();
}

void Agent::init () {
	if (parent != nullptr)
		parent->children.insert(shared_from_this());
}

Agent::~Agent () {
	lock_guard<recursive_mutex> lock(parent_m);

	delete properties;
}

AgentPtr Agent::getParent () {
	return parent;
}

void Agent::reparent () {
	lock_guard<recursive_mutex> lock(parent_m);

	if (parent == nullptr)
		return;

	lock_guard<recursive_mutex> pLock(parent->parent_m);

	parent->children.erase(this->shared_from_this());

	auto grandParent = parent->parent;

	if (grandParent == nullptr) {
		parent = nullptr;
	}
	else {
		lock_guard<recursive_mutex> gpLock(grandParent->parent_m);

		grandParent->children.insert(this->shared_from_this());

		parent = grandParent;
	}
}

void Agent::unparent () {
	lock_guard<recursive_mutex> lock(parent_m);

	if (parent == nullptr)
		return;

	lock_guard<recursive_mutex> pLock(parent->parent_m);

	parent->children.erase(this->shared_from_this());

	// TODO si child non dans les enfants acutels, lever erreur
	// TODO retirer this de la liste des enfants du parent

	parent = nullptr;
}

void Agent::setProperty (string key, ValuePtr value) {
	lock_guard<recursive_mutex> lock(parent_m);

	// Standard functions
	if (key == "print")
		return;

	if (key == "println")
		return;

	if (key == "rand")
		return;

	if (key == "random")
		return;

	if (key == "type_of")
		return;

	// Standard colors
	if (key == "black")
		return;

	if (key == "white")
		return;

	if (key == "grey")
		return;

	if (key == "red")
		return;

	if (key == "green")
		return;

	if (key == "blue")
		return;

	if (key == "yellow")
		return;

	if (key == "cyan")
		return;

	if (key == "magenta")
		return;

	// Other properties
	auto prop = pair<string, ValuePtr>(key, value);

	auto search = properties->find (key);
	if ( search != properties->end())
		properties->erase(key);

	if (value->getType() != Type::NIL)
		properties->insert(prop);
}

ValuePtr Agent::getProperty(string p) {
	lock_guard<recursive_mutex> lock(parent_m);

	// Standard functions
	if (p == "print")
		return PrintFunction::getInstance();

	if (p == "println")
		return PrintlnFunction::getInstance();

	if (p == "rand")
		return RandFunction::getInstance();

	if (p == "random")
		return RandomFunction::getInstance();

	if (p == "type_of")
		return TypeOfFunction::getInstance();

	// Standard colors
	if (p == "black")
		return make_shared<Color>(0.0, 0.0, 0.0);

	if (p == "white")
		return make_shared<Color>(1.0, 1.0, 1.0);

	if (p == "grey")
		return make_shared<Color>(0.5, 0.5, 0.5);

	if (p == "red")
		return make_shared<Color>(1.0, 0.0, 0.0);

	if (p == "green")
		return make_shared<Color>(0.0, 1.0, 0.0);

	if (p == "blue")
		return make_shared<Color>(0.0, 0.0, 1.0);

	if (p == "yellow")
		return make_shared<Color>(1.0, 1.0, 0.0);

	if (p == "cyan")
		return make_shared<Color>(0.0, 1.0, 1.0);

	if (p == "magenta")
		return make_shared<Color>(1.0, 0.0, 1.0);

	// Other properties
	unordered_map<string,ValuePtr>::const_iterator got = properties->find(p);

	if (got == properties->end())
		return Nil::getInstance();

	return got->second;
}

unordered_map<string,ValuePtr>* Agent::getProperty() {
	lock_guard<recursive_mutex> lock(parent_m);
	return properties;
}

int Agent::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Agent>(other));
}

int Agent::compare(AgentPtr other) {
	return this - other.get();
}

void Agent::exportProperties(Object* o){
	unordered_map<string,ValuePtr>* properties=Agent::getProperty();
	Object p;
	for (auto m : *properties)
	{
		if (m.second->getType() == Type::COLOR)
			p.push_back(Pair(m.first,dynamic_pointer_cast<Color>(m.second)->toString()));
		if (m.second->getType() == Type::NUMBER)
			p.push_back(Pair(m.first,dynamic_pointer_cast<Number>(m.second)->getValue()));
		if (m.second->getType() == Type::STRING)
			p.push_back(Pair(m.first,dynamic_pointer_cast<String>(m.second)->toString()));
		if (m.second->getType() == Type::BOOLEAN)
			p.push_back(Pair(m.first,dynamic_pointer_cast<Boolean>(m.second)->toString()));
	}
	o->push_back(Pair("properties",p));
}

void Agent::destroy () {
	auto p = parent;
	for(auto t : children)
		this->reparent();
	this->unparent();
	parent = p;
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
