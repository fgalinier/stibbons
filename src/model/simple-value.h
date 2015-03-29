/**
 * \file simple-value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.2
 * \date 14/03/2015
 */

#pragma once

#include <mutex>

using namespace std;

namespace stibbons {

/**
 * \class SimpleValue
 *
 * \brief A class representing a simple value.
 *
 * \author Adrien Plazas
 */
template<typename T>
class SimpleValue {
	public:
		/**
		 * Set the value of value
		 * @param value the new value of value
		 */
		void setValue (const T& value) {
			lock_guard<mutex> lock(value_m);
			this->value = value;
		}

		/**
		 * Get the value of value
		 * @return the value of value
		 */
		T getValue () {
			lock_guard<mutex> lock(value_m);
			return value;
		}

		SimpleValue() = default;
		SimpleValue(T value) : value(value) {}

		// Move initialization
		SimpleValue (SimpleValue&& other) {
			lock_guard<mutex> lock(other.value_m);

			// Set this
			value = move(other.value);

			// Reset other
		}

		// Copy initialization
		SimpleValue(SimpleValue& other) {
			lock_guard<mutex> lock(other.value_m);

			// Set this
			value = other.value;
		}

		// Move assignment
		SimpleValue& operator = (SimpleValue&& other) {
			if (this == &other)
				return *this;

			lock(value_m, other.value_m);
			lock_guard<mutex> self_lock(value_m, adopt_lock);
			lock_guard<mutex> other_lock(other.value_m, adopt_lock);

			// Set this
			value = move(other.value);

			// Reset other

			return *this;
		}

		// Copy assignment
		SimpleValue& operator = (SimpleValue& other) {
			if (this == &other)
				return *this;

			lock(value_m, other.value_m);
			lock_guard<mutex> self_lock(value_m, adopt_lock);
			lock_guard<mutex> other_lock(other.value_m, adopt_lock);

			// Set this
			value = other.value;

			return *this;
		}

	protected:
		T value;
		mutex value_m;
};

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
