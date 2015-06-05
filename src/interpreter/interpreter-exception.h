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
 * \file interpreter-exception.h
 * \brief InterpreterException class header.
 * \author Florian Galinier
 * \version 1.1
 * \date 28/03/15
 *
 * Declaration of InterpreterException class inherited by syntax and semantic
 * exceptions.
 *
 */

#pragma once

#include <exception>
#include <string>
#include <sstream>
#include "y.tab.h"

namespace stibbons {

	/**
	 * \class InterpreterException
	 * \brief Abstraction of interpreter exceptions.
	 *
	 * This kind of exception contains a error message and a position.
	 *
	 * \author Florian Galinier
	 */
	class InterpreterException : public std::exception { 
	private: 
		std::string msg;
		yy::position pos;

	public: 
		/**
		 * Create a new InterpreterException
		 * \param msg The error message.
		 * \param pos The position of error.
		 */
		InterpreterException(const char*, yy::position);   

		/**
		 * Create a new InterpreterException
		 * \param msg The error message.
		 * \param pos The position of error.
		 */
		InterpreterException(std::string msg, yy::position);

		/**
		 * Return a message with the error that occurred.
		 * \return A message with the error and the position
		 */
		virtual const char* what() const throw() =0;  
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
