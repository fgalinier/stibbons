#include "agent.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

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

	parent = parent;
}

void Agent::setProperty (string key, ValuePtr value) {
	lock_guard<recursive_mutex> lock(parent_m);

	auto prop = pair<string, ValuePtr>(key, value);

	auto search = properties->find (key);
	if ( search == properties->end())
		properties->insert(prop);
	else {
		properties->erase(key);
		properties->insert(prop);
	}
}

ValuePtr Agent::getProperty(string p) {
	lock_guard<recursive_mutex> lock(parent_m);

	unordered_map<string,ValuePtr>::const_iterator got = properties->find(p);

	if (got == properties->end())
		return (parent == nullptr) ? Nil::getInstance() :
		                             parent->getProperty(p);

	return got->second;
}

int Agent::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Agent>(other));
}

int Agent::compare(AgentPtr other) {
	return this - other.get();
}

void Agent::initColors() {
	setProperty("black", make_shared<Color>(0.0, 0.0, 0.0));
	setProperty("white", make_shared<Color>(1.0, 1.0, 1.0));

	setProperty("grey", make_shared<Color>(0.5, 0.5, 0.5));

	setProperty("red", make_shared<Color>(1.0, 0.0, 0.0));
	setProperty("green", make_shared<Color>(0.0, 1.0, 0.0));
	setProperty("blue", make_shared<Color>(0.0, 0.0, 1.0));

	setProperty("yellow", make_shared<Color>(1.0, 1.0, 0.0));
	setProperty("cyan", make_shared<Color>(0.0, 1.0, 1.0));
	setProperty("magenta", make_shared<Color>(1.0, 0.0, 1.0));
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
