#pragma once
#include "value.h"
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <mutex>

using namespace std;

namespace stibbons {
/**
 * \class Table
 *
 * \brief class Table in stibbons
 */
class Table : public GenericValue<Type::TABLE> {
	public:
		/**
		 * Empty Constructor
		 */
		Table () = default;

		/**
		 * Add a value
		 * @param pair the key-value pair to set
		 */
		virtual void setValue (pair<string, Value*> pair);

		/**
		 * Add a value
		 * @param key the key of the value
		 * @param value the value of the value
		 */
		virtual void setValue (string key, Value* value);

		 /**
		 * Get a value
		 * @param key the key
		 * @return the value
		 */
		 virtual Value* getValue(string key);

		 /**
		 * Get a string representing the table
		 * @return a string representing the table
		 */
		 virtual string toString();

	protected :
		mutex value_m;

	private:
		unordered_map<string, Value*> values;

		void tryDelete (Value* value) throw (domain_error);
};
}
/*
 * Editor modelines-http://www.wireshark.org/tools/modelines.html
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
