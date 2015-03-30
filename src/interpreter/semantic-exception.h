/**
 * \file semantic-exception.h
 * \brief SemanticException class header.
 * \author Florian Galinier
 * \version 0.2
 * \date 28/03/15
 *
 * Declaration of SemanticException class, used to prevent when interpreter find a
 * semantic error.
 *
 */

#include "interpreter-exception.h"

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