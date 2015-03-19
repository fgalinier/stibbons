/**
 * \file boolean.h
 * \brief A class representing a boolean
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.2
 * \date 14/03/2015
 */

#pragma once

#include "value.h"

namespace stibbons {

/**
 * class Boolean
 *
 *\brief A class representing a boolean.
 *
 *\author Julia Bassoumi
 */
class Boolean : public Value {
	public:
		/**
		 * Create a boolean from a 
		 */
		Boolean (bool value = false);

		Type getType () const;

		/**
		 * Set the value of value
		 * @param new_var the new value of value
		 */
		void setValue (bool new_var);

		/**
		 * Get the value of value
		 * @return the value of value
		 */
		bool getValue () const;

	private:
		bool value;
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
