/**
 * \file number.h
 * \brief A class representing a real number
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.1
 * \date 14/03/2015
 */

#pragma once

#include "value.h"

namespace stibbons {

/**
 * class Number
 *
 *\brief A class representing a real number.
 *
 *\author Julia Bassoumi
 */
class Number : public Value {
	public:
		/**
		 * Create a Number with its value
		 * @param value the value of the number
		 */
		Number (double value = 0.0);

		Type getType() const;

		/**
		 * Set the value of value
		 * @param new_var the new value of value
		 */
		void setValue (double new_var);

		/**
		 * Get the value of value
		 * @return the value of value
		 */
		double getValue ();

	private:
		double value;
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
