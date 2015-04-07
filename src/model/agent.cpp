#include "agent.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

#include <cmath>

namespace stibbons {

Agent::Agent (Agent *parent) : parent(parent) {
	properties=new unordered_map<string,Value*>();

	if (parent != nullptr)
		parent->children.insert(this);
}

Agent::~Agent () {
	lock_guard<mutex> lock(parent_m);

	for (auto value : *properties) {
		tryDelete (value.second);
	}

	delete properties;
}

Agent* Agent::getParent () {
	return parent;
}

void Agent::reparent () {
	lock_guard<mutex> lock(parent_m);

	if (parent == nullptr)
		return;

	lock_guard<mutex> pLock(parent->parent_m);

	parent->children.erase(this);

	auto grandParent = parent->parent;

	if (grandParent == nullptr) {
		parent = nullptr;
	}
	else {
		lock_guard<mutex> gpLock(grandParent->parent_m);

		grandParent->children.insert(this);

		parent = grandParent;
	}
}

void Agent::unparent () {
	lock_guard<mutex> lock(parent_m);

	if (parent == nullptr)
		return;

	lock_guard<mutex> pLock(parent->parent_m);

	parent->children.erase(this);

	// TODO si child non dans les enfants acutels, lever erreur
	// TODO retirer this de la liste des enfants du parent

	parent = parent;
}

void Agent::setProperty (pair<string,Value*> &&new_var) {
	lock_guard<mutex> lock(parent_m);

	auto search = properties->find (new_var.first);
	if ( search == properties->end())
		properties->insert(new_var);
	else {
		tryDelete (search->second);
		properties->erase(new_var.first);
		properties->insert(new_var);
	}
}

void Agent::setProperty (pair<string,Value*> &new_var) {
	lock_guard<mutex> lock(parent_m);

	auto search = properties->find (new_var.first);
	if ( search == properties->end())
		properties->insert(new_var);
	else {
		tryDelete (search->second);
		properties->erase(new_var.first);
		properties->insert(new_var);
	}
}

Value* Agent::getProperty(string p) {
	lock_guard<mutex> lock(parent_m);

	unordered_map<string,Value*>::const_iterator got = properties->find(p);

	if (got == properties->end())
		return (parent == nullptr) ? &Nil::getInstance() :
		                             parent->getProperty(p);

	return got->second;
}

void Agent::tryDelete (Value* value) throw (domain_error) {
	switch (value->getType()) {
		case Type::NIL:
			break;
		case Type::NUMBER:
			delete dynamic_cast<Number*> (value);
			break;
		case Type::BOOLEAN:
			delete dynamic_cast<Boolean*> (value);
			break;
		case Type::STRING:
			delete dynamic_cast<String*> (value);
			break;
		case Type::COLOR:
			delete dynamic_cast<Color*> (value);
			break;
		default:
			throw domain_error("Unexpected value type.");
	}
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
