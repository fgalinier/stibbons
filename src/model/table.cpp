#include "table.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

//#include <cmath>

using namespace std;

namespace stibbons {

	void Table::setValue (pair<string, ValuePtr> pair) {
		lock_guard<mutex> lock(value_m);

		auto search = values.find (pair.first);
		if ( search == values.end())
			values.insert(pair);
		else {
			//tryDelete (search->second);
			values.erase(pair.first);
			values.insert(pair);
		}
	}

	void Table::setValue (string key, ValuePtr value) {
		setValue (pair<string, ValuePtr>(key, value));
	}

	ValuePtr Table::getValue(string key) {
		lock_guard<mutex> lock(value_m);

		unordered_map<string,ValuePtr>::const_iterator got = values.find(key);

		if (got == values.end())
			return make_shared<Nil>();

		return got->second;
	}

	int Table::compare (ValuePtr other) {
		if (getType() != other->getType())
			return Value::compare (other);

		return compare (dynamic_pointer_cast<Table>(other));
	}

	int Table::compare(TablePtr other) {
		return other.get() - this;
	}

	string Table::toString() {
		lock_guard<mutex> lock(value_m);

		string str = "{\n";

		for (auto value : values)
			str += "\t" + value.first + ": " + value.second->toString() + "\n";

		str += "}\n";

		return str;
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
