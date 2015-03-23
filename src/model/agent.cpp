#include "agent.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

#include <cmath>

namespace stibbons {

Agent::Agent () {
	properties=new unordered_map<string,Value*>();
}

Agent::~Agent () {
	for (auto value : *properties) {
		tryDelete (value.second);
	}

	delete properties;
}

void Agent::setProperty (pair<string,Value*> &new_var) {
	auto search = properties->find (new_var.first);
	if ( search == properties->end())
		properties->insert(new_var);
	else {
		tryDelete (search->second);
		properties->erase(new_var.first);
		properties->insert(new_var);
	}
}

unordered_map<string,Value*> Agent::getProperties() const {
	return *properties;
}

Value* Agent::getProperty(string p) {
	unordered_map<string,Value*>::const_iterator got = properties->find(p);

	if ( got == properties->end())
		return &Nil::getInstance();

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
