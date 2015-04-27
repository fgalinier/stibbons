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
	lock_guard<mutex> lock(parent_m);

	delete properties;
}

AgentPtr Agent::getParent () {
	return parent;
}

void Agent::reparent () {
	lock_guard<mutex> lock(parent_m);

	if (parent == nullptr)
		return;

	lock_guard<mutex> pLock(parent->parent_m);

	parent->children.erase(this->shared_from_this());

	auto grandParent = parent->parent;

	if (grandParent == nullptr) {
		parent = nullptr;
	}
	else {
		lock_guard<mutex> gpLock(grandParent->parent_m);

		grandParent->children.insert(this->shared_from_this());

		parent = grandParent;
	}
}

void Agent::unparent () {
	lock_guard<mutex> lock(parent_m);

	if (parent == nullptr)
		return;

	lock_guard<mutex> pLock(parent->parent_m);

	parent->children.erase(this->shared_from_this());

	// TODO si child non dans les enfants acutels, lever erreur
	// TODO retirer this de la liste des enfants du parent

	parent = parent;
}

void Agent::setProperty (pair<string,ValuePtr> &&new_var) {
	lock_guard<mutex> lock(parent_m);

	auto search = properties->find (new_var.first);
	if ( search == properties->end())
		properties->insert(new_var);
	else {
		properties->erase(new_var.first);
		properties->insert(new_var);
	}
}

void Agent::setProperty (pair<string,ValuePtr> &new_var) {
	lock_guard<mutex> lock(parent_m);

	auto search = properties->find (new_var.first);
	if ( search == properties->end())
		properties->insert(new_var);
	else {
		properties->erase(new_var.first);
		properties->insert(new_var);
	}
}

void Agent::setProperty (string key, ValuePtr value) {
	setProperty (pair<string, ValuePtr>(key, value));
}

ValuePtr Agent::getProperty(string p) {
	lock_guard<mutex> lock(parent_m);

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
