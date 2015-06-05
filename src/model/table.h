/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

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
		 * \param pair the key-value pair to set
		 */
		virtual void setValue (pair<string, ValuePtr> pair);

		/**
		 * Add a value
		 * \param key the key of the value
		 * \param value the value of the value
		 */
		virtual void setValue (string key, ValuePtr value);

		 /**
		 * Get a value
		 * \param key the key
		 * \return the value
		 */
		 virtual ValuePtr getValue(string key);

		 /**
		 * Check if a key exists in the table
		 * \param key the key
		 * \return wether the key exists or not
		 */
		 virtual bool exists(string key);

		 /**
		 * Get all the named values
		 * \return values contained in the table
		 */
		 virtual const unordered_map<string, ValuePtr>& getNamedValues();

		 /**
		 * Get all the indexed values
		 * \return values contained in the table
		 */
		 virtual const map<long, ValuePtr>& getIndexedValues();

		/**
		 * Add a value
		 * \param pair the key-value pair to set
		 */
		virtual void setValue (pair<long, ValuePtr> pair);

		/**
		 * Add a value
		 * \param key the key of the value
		 * \param value the value of the value
		 */
		virtual void setValue (long key, ValuePtr value);

		/**
		 * Add a value to the end
		 * \param value the value of the value
		 */
		virtual void append (ValuePtr value);

		 /**
		 * Get a value
		 * \param key the key
		 * \return the value
		 */
		 virtual ValuePtr getValue(long key);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a negative number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * \param other the other value
		 * \return the comparison value of this and the other value
		 */
		virtual double compare (ValuePtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a positive number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * \param other the other value
		 * \return the comparison value of this and the other value
		 */
		virtual double compare (TablePtr other);

		 /**
		 * Get a string representing the table
		 * \return a string representing the table
		 */
		 virtual string toString();	

		 /**
		 * Get the length of the table
		 * \return a int representing the table's length
		 */
		 virtual int length();

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
