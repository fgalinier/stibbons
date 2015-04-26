#include "table.h"

#include "boolean.h"
#include "color.h"
#include "nil.h"
#include "number.h"
#include "string.h"

#include <sstream>

using namespace std;

namespace stibbons {

	void Table::setValue (pair<string, ValuePtr> pair) {
		lock_guard<mutex> lock(value_m);

		auto search = namedValues.find (pair.first);
		if ( search == namedValues.end())
			namedValues.insert(pair);
		else {
			//tryDelete (search->second);
			namedValues.erase(pair.first);
			namedValues.insert(pair);
		}
	}

	void Table::setValue (string key, ValuePtr value) {
		setValue (pair<string, ValuePtr>(key, value));
	}

	ValuePtr Table::getValue(string key) {
		lock_guard<mutex> lock(value_m);

		auto got = namedValues.find(key);

		if (got == namedValues.end())
			return Nil::getInstance();

		return got->second;
	}

	void Table::setValue (pair<long, ValuePtr> pair) {
		lock_guard<mutex> lock(value_m);

		auto search = indexedValues.find (pair.first);
		if ( search == indexedValues.end())
			indexedValues.insert(pair);
		else {
			//tryDelete (search->second);
			indexedValues.erase(pair.first);
			indexedValues.insert(pair);
		}
	}

	void Table::setValue (long key, ValuePtr value) {
		setValue (pair<long, ValuePtr>(key, value));
	}

	void Table::append (ValuePtr value) {
		lock_guard<mutex> lock(value_m);

		long key = indexedValues.rbegin()->first + 1;

		indexedValues.insert(pair<long, ValuePtr>(key, value));
	}

	ValuePtr Table::getValue(long key) {
		lock_guard<mutex> lock(value_m);

		auto got = indexedValues.find(key);

		if (got == indexedValues.end())
			return Nil::getInstance();

		return got->second;
	}

	int Table::compare (ValuePtr other) {
		if (getType() != other->getType())
			return Value::compare (other);

		return compare (dynamic_pointer_cast<Table>(other));
	}

	int Table::compare(TablePtr other) {
		return this - other.get() ;
	}

	string Table::toString() {
		lock_guard<mutex> lock(value_m);

		std::ostringstream oss;

		oss << "{\n";

		for (auto value : indexedValues)
			oss << "\t" << value.first << ": " << value.second->toString() << "\n";

		for (auto value : namedValues)
			oss << "\t" << value.first << ": " << value.second->toString() << "\n";

		oss << "}\n";

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
