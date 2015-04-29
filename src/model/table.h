#pragma once
#include "value.h"
#include <map>
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
		virtual void setValue (pair<string, ValuePtr> pair);

		/**
		 * Add a value
		 * @param key the key of the value
		 * @param value the value of the value
		 */
		virtual void setValue (string key, ValuePtr value);

		 /**
		 * Get a value
		 * @param key the key
		 * @return the value
		 */
		 virtual ValuePtr getValue(string key);

		/**
		 * Add a value
		 * @param pair the key-value pair to set
		 */
		virtual void setValue (pair<long, ValuePtr> pair);

		/**
		 * Add a value
		 * @param key the key of the value
		 * @param value the value of the value
		 */
		virtual void setValue (long key, ValuePtr value);

		/**
		 * Add a value to the end
		 * @param value the value of the value
		 */
		virtual void append (ValuePtr value);

		 /**
		 * Get a value
		 * @param key the key
		 * @return the value
		 */
		 virtual ValuePtr getValue(long key);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a negative number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual int compare (ValuePtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a positive number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual int compare (TablePtr other);

		 /**
		 * Get a string representing the table
		 * @return a string representing the table
		 */
		 virtual string toString();

	protected :
		recursive_mutex value_m;

	private:
		unordered_map<string, ValuePtr> namedValues;
		map<long, ValuePtr> indexedValues;

		void tryDelete (ValuePtr value) throw (domain_error);
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
