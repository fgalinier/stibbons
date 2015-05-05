/**
 * \file type-value.h
 * \brief A class representing a type
 * \author Adrien Plazas
 * \version 0.5
 * \date 29/04/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"

#include <memory>

namespace stibbons {

/**
 * class TypeValue
 *
 *\brief A class representing a type.
 *
 *\author Adrien Plazas
 */
class TypeValue : public GenericValue<Type::TYPE>, public SimpleValue<Type> {
	public:
		using SimpleValue<Type>::SimpleValue;
		virtual ~TypeValue () = default;

		virtual void reset ();

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
		virtual int compare (TypeValuePtr other);

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();
};

typedef std::shared_ptr<TypeValue> TypeValuePtr;

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
