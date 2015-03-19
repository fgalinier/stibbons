/**
 * \file simple-value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.2
 * \date 14/03/2015
 */

#pragma once

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
			this->value = value;
		}

		/**
		 * Get the value of value
		 * @return the value of value
		 */
		T& getValue () {
			return value;
		}

	public:
		SimpleValue() = default;
		SimpleValue(T value) : value(value) {}

		T value;
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
