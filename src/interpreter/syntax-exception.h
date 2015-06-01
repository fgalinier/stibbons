/**
 * \file syntax-exception.h
 * \brief SyntaxException class header.
 * \author Florian Galinier
 * \version 1.1
 * \date 28/03/15
 *
 * Declaration of SyntaxException class, used to prevent when parser find a
 * syntax error.
 *
 */

#pragma once

#include "interpreter-exception.h"

namespace stibbons {

	/**
	 * \class SyntaxException
	 * \brief Exception thrown when a syntax error occurred.
	 *
	 * This exception is used to inform that a syntax error occurred.
	 *
	 * \author Florian Galinier
	 */
	class SyntaxException : public InterpreterException { 
	private: 
		std::string msg;
		yy::position pos;

	public: 
		/**
		 * Create a new SyntaxException
		 * \param msg The error message.
		 * \param pos The position of error.
		 */
		SyntaxException(const char*, yy::position);   
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
