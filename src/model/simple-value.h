/**
 * \file simple-value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.2
 * \date 14/03/2015
 */

#pragma once

#include <mutex>

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
			std::lock_guard<std::mutex> lock(value_m);
			this->value = value;
		}

		/**
		 * Get the value of value
		 * @return the value of value
		 */
		T& getValue () {
			std::lock_guard<std::mutex> lock(value_m);
			return value;
		}

	public:
		SimpleValue() = default;
		SimpleValue(T value) : value(value) {}

		// Move initialization
		SimpleValue (SimpleValue&& other) {
			std::lock_guard<std::mutex> lock(other.value_m);
			value = std::move(other.value);
			// FIXME set other's value to the default
		}

		// Copy initialization
		SimpleValue(const SimpleValue& other) {
			std::lock_guard<std::mutex> lock(other.value_m);
			value = other.value;
		}

		// Move assignment
		SimpleValue& operator = (SimpleValue&& other) {
			std::lock(value_m, other.value_m);
			std::lock_guard<std::mutex> self_lock(value_m, std::adopt_lock);
			std::lock_guard<std::mutex> other_lock(other.value_m, std::adopt_lock);
			value = std::move(other.value);
			other.value = 0;
			return *this;
		}

		// Copy assignment
		SimpleValue& operator = (const SimpleValue& other) {
			std::lock(value_m, other.value_m);
			std::lock_guard<std::mutex> self_lock(value_m, std::adopt_lock);
			std::lock_guard<std::mutex> other_lock(other.value_m, std::adopt_lock);
			value = other.value;
			return *this;
		}

		T value;
		std::mutex value_m;
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
