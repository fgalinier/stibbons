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
 * \file semantic-exception.h
 * \brief SemanticException class header.
 * \author Florian Galinier
 * \version 1.1
 * \date 28/03/15
 *
 * Declaration of SemanticException class, used to prevent when interpreter find a
 * semantic error.
 *
 */

#pragma once

#include "interpreter-exception.h"

#include "../model/type.h"

#include <string>

using namespace std;

namespace stibbons {

	/**
	 * \class SemanticException
	 * \brief Exception thrown when a semantic error occurred.
	 *
	 * This exception is used to inform that a semantic error occurred.
	 *
	 * \author Florian Galinier
	 */
	class SemanticException : public InterpreterException { 
	public:
		/**
		 * Create a new SemanticException
		 * \param msg The error message.
		 * \param pos The position of error.
		 */
		SemanticException(const char*, yy::position);

		/**
		 * Create a new SemanticException
		 * \param msg The error message.
		 * \param expectedType The expected type.
		 * \param actualType The actual type.
		 * \param pos The position of error.
		 */
		SemanticException(std::string msg, Type expectedType, Type actualType, yy::position pos);

		/**
		 * Create a new SemanticException
		 * \param msg The error message.
		 * \param expectedType1 The first expected type.
		 * \param expectedType2 The second expected type.
		 * \param actualType1 The first actual type.
		 * \param actualType2 The second actual type.
		 * \param pos The position of error.
		 */
		SemanticException(std::string msg, Type expectedType1, Type expectedType2, Type actualType1, Type actualType2, yy::position pos);
	
		/**
		 * Create a new SemanticException
		 * \param msg The error message.
		 * \param expectedType1 One of the expected type.
		 * \param expectedType2 The other expected type.
		 * \param actualType The actual type.
		 * \param pos The position of error.
		 */
		SemanticException(std::string msg, Type expectedType1, Type expectedType2, Type actualType, yy::position pos);
		
		/**
		 * Return a message with the error that occurred.
		 * \return A message with the error and the position
		 */
		virtual const char* what() const throw(); 
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
