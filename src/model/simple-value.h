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

/**
 * \file simple-value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
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
		 * Get the value of value
		 * \return the value of value
		 */
		T getValue () {
			lock_guard<recursive_mutex> lock(value_m);
			return value;
		}

		SimpleValue() = default;

		/**
		 * Copy constructor.
		 * \param value the value to copy
		 */
		SimpleValue(T value) : value(value) {}

		/**
		 * Move initialization.
		 * \param other the value to move
		 */
		SimpleValue (SimpleValue&& other) {
			lock_guard<recursive_mutex> lock(other.value_m);

			// Set this
			value = move(other.value);

			// Reset other
			other.reset();
		}

		/**
		 * Copy initialization.
		 * \param other the value to copy
		 */
		SimpleValue(SimpleValue& other) {
			lock_guard<recursive_mutex> lock(other.value_m);

			// Set this
			value = other.value;
		}

		/**
		 * Move assignment.
		 * \param other the value to move
		 */
		SimpleValue& operator = (SimpleValue&& other) {
			if (this == &other)
				return *this;

			lock(value_m, other.value_m);
			lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
			lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

			// Set this
			value = move(other.value);

			// Reset other
			other.reset();

			return *this;
		}

		/**
		 * Copy assignment.
		 * \param other the value to copy.
		 */
		SimpleValue& operator = (SimpleValue& other) {
			if (this == &other)
				return *this;

			lock(value_m, other.value_m);
			lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
			lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

			// Set this
			value = other.value;

			return *this;
		}

	protected:
		/**
		 * Reset to the default value
		 */
		virtual void reset () =0;

		T value;
		recursive_mutex value_m;
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
