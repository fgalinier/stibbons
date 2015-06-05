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
 * \file value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
 * \date 14/03/2015
 */

#pragma once

#include "type.h"

#include <memory>
#include <stdexcept>

namespace stibbons {

/**
 * \class Value
 *
 * \brief An abstract class who represent a values of a given type.
 *
 * \author Julia Bassoumi
 */
class Value {
	public:
		/**
		 * Return the type of the value
		 * \return a Type
		 */
		virtual Type getType() const=0;

		/**
		 * Add a value to another
		 * \param other the other value
		 * \return the resulting value
		 */
		virtual ValuePtr add (ValuePtr other) throw(std::domain_error) {
			throw std::domain_error("Can't add a " + stibbons::toString(getType()) + " and a " + stibbons::toString(other->getType()));
		}

		/**
		 * Substract a value to another
		 * \param other the other value
		 * \return the resulting value
		 */
		virtual ValuePtr substract (ValuePtr other) throw(std::domain_error) {
			throw std::domain_error("Can't substract a " + stibbons::toString(getType()) + " and a " + stibbons::toString(other->getType()));
		}

		/**
		 * Multiply a value to another
		 * \param other the other value
		 * \return the resulting value
		 */
		virtual ValuePtr multiply (ValuePtr other) throw(std::domain_error) {
			throw std::domain_error("Can't multiply a " + stibbons::toString(getType()) + " and a " + stibbons::toString(other->getType()));
		}

		/**
		 * Divide a value to another
		 * \param other the other value
		 * \return the resulting value
		 */
		virtual ValuePtr divide (ValuePtr other) throw(std::domain_error) {
			throw std::domain_error("Can't divide a " + stibbons::toString(getType()) + " and a " + stibbons::toString(other->getType()));
		}

		/**
		 * Get the remainder of the division of a value to another
		 * \param other the other value
		 * \return the resulting value
		 */
		virtual ValuePtr modulo (ValuePtr other) throw(std::domain_error) {
			throw std::domain_error("Can't divide a " + stibbons::toString(getType()) + " and a " + stibbons::toString(other->getType()));
		}

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
		virtual double compare (ValuePtr other) {
			return ((long) getType()) - ((long) other->getType());
		}

		/**
		 * Return whether this value is equal to the other
		 *
		 * \param other the other value
		 * \return whether this value is equal to the other
		 */
		virtual bool isEqual (ValuePtr other) {
			return compare(other) == 0;
		}

		/**
		 * Return whether this value is different from the other
		 *
		 * \param other the other value
		 * \return whether this value is different from the other
		 */
		virtual bool isDifferent (ValuePtr other) {
			return compare(other) != 0;
		}

		/**
		 * Return whether this value is lower than the other
		 *
		 * \param other the other value
		 * \return whether this value is lower than the other
		 */
		virtual bool isLower (ValuePtr other) {
			return compare(other) < 0;
		}

		/**
		 * Return whether this value is greater than the other
		 *
		 * \param other the other value
		 * \return whether this value is greater than the other
		 */
		virtual bool isGreater (ValuePtr other) {
			return compare(other) > 0;
		}

		/**
		 * Return whether this value is lower than or equal to the other
		 *
		 * \param other the other value
		 * \return whether this value is lower than or equal to the other
		 */
		virtual bool isLowerOrEqual (ValuePtr other) {
			return compare(other) <= 0;
		}

		/**
		 * Return whether this value is greater than or equal to the other
		 *
		 * \param other the other value
		 * \return whether this value is greater than or equal to the other
		 */
		virtual bool isGreaterOrEqual (ValuePtr other) {
			return compare(other) >= 0;
		}

		/**
		 * Return a string corresponding to the value
		 * \return a string corresponding to the value
		 */
		virtual std::string toString ()=0;
};

/**
 * \class GenericValue
 *
 * \brief An template class easing the implementation of a Value class.
 *
 * \author Adrien Plazas
 */
template<Type T>
class GenericValue : public virtual Value {
	public:
		/**
		 * Return the type of the value
		 * \return a value of the enumeration Type
		 */
		virtual Type getType() const {
			return T;
		}
};

typedef std::shared_ptr<Value> ValuePtr;

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
