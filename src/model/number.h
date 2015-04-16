/**
 * \file number.h
 * \brief A class representing a real number
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.3
 * \date 14/03/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"

#include <memory>

namespace stibbons {

/**
 * class Number
 *
 *\brief A class representing a real number.
 *
 *\author Julia Bassoumi, Adrien Plazas
 */
class Number : public GenericValue<Type::NUMBER>, public SimpleValue<double> {
	public:
		using SimpleValue<double>::SimpleValue;
		virtual ~Number () = default;

		virtual void reset ();

		/**
		 * Add a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr add (ValuePtr other) throw(std::domain_error);

		/**
		 * Add a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual NumberPtr add (NumberPtr other);

		/**
		 * Substract a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr substract (ValuePtr other) throw(std::domain_error);

		/**
		 * Substract a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual NumberPtr substract (NumberPtr other);

		/**
		 * Multiply a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr multiply (ValuePtr other) throw(std::domain_error);

		/**
		 * Multiply a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual NumberPtr multiply (NumberPtr other);

		/**
		 * Divide a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr divide (ValuePtr other) throw(std::domain_error);

		/**
		 * Divide a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual NumberPtr divide (NumberPtr other) throw(std::domain_error);

		/**
		 * Get the remainder of the division of a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr modulo (ValuePtr other) throw(std::domain_error);

		/**
		 * Get the remainder of the division of a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual NumberPtr modulo (NumberPtr other) throw(std::domain_error);

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
		 * return a negative number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual int compare (NumberPtr other);

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();
};

typedef std::shared_ptr<Number> NumberPtr;

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
