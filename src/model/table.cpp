#include "table.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

//#include <cmath>

using namespace std;

namespace stibbons {

Table::~Table () {
	lock_guard<mutex> lock(value_m);

	for (auto value : values) {
		tryDelete (value.second);
	}
}

void Table::setValue (pair<string, Value*> pair) {
	lock_guard<mutex> lock(value_m);

	auto search = values.find (pair.first);
	if ( search == values.end())
		values.insert(pair);
	else {
		tryDelete (search->second);
		values.erase(pair.first);
		values.insert(pair);
	}
}

void Table::setValue (string key, Value* value) {
	setValue (pair<string, Value*>(key, value));
}

Value* Table::getValue(string key) {
	lock_guard<mutex> lock(value_m);

	unordered_map<string,Value*>::const_iterator got = values.find(key);

	if (got == values.end())
		return &Nil::getInstance();

	return got->second;
}

string Table::toString() {
	lock_guard<mutex> lock(value_m);

	string str = "{\n";

	for (auto value : values)
		str += "\t" + value.first + ": " + value.second->toString() + "\n";

	str += "}\n";

	return str;
}

void Table::tryDelete (Value* value) throw (domain_error) {
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
