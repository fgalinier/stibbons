/**
 * \file boolean.h
 * \brief A class representing a boolean
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.3
 * \date 14/03/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"

namespace stibbons {

/**
 * class Boolean
 *
 *\brief A class representing a boolean.
 *
 *\author Julia Bassoumi, Adrien Plazas
 */
class Boolean : public GenericValue<Type::BOOLEAN>, public SimpleValue<bool> {
	public:
		using SimpleValue<bool>::SimpleValue;
		virtual ~Boolean () = default;

		virtual void reset ();

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();
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
