/**
 * \file string.h
 * \brief A class representing a string
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.1
 * \date 14/03/2015
 */

#pragma once

#include "value.h"

#include <string>

namespace stibbons {

/**
 * \class String
 *
 * \brief A class representing a string.
 *
 * \author Julia Bassoumi
 */
class String : public Value {
	public:
		/**
		 * Create a string
		 *@param s the value of the string
		 */
		String (std::string s = "");

		Type getType() const;

		/**
		 * Set the value of value
		 * @param new_var the new value of value
		 */
		void setValue (std::string new_var);

		/**
		 * Get the value of value
		 * @return the value of value
		 */
		std::string getValue ();

	private:
		std::string value;
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
