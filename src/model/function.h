/**
 * \file function.h
 * \brief A class representing a function
 * \author Julia Bassoumi
 * \version 0.3
 * \date 28/03/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"
#include "../interpreter/tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

namespace stibbons {

/**
 * class Function
 *
 *\brief A class representing a function.
 *
 *\author Julia Bassoumi
**/

class Function : public GenericValue<Type::FUNCTION>, public SimpleValue<Tree*>{
	public:
		using SimpleValue<Tree*>::SimpleValue;

		/**
		* Constructor
		*/
		Function (Tree* arbre = new Tree(0,nullptr),vector<string> l = vector<string>());

		/**
		* Destructor
		*/
		virtual ~Function ( ) = default;

		/**
		* Set the value of argument
		* @param r the new value of arg
		*/
		void setArg (string r);

		/**
		* Get the list of arg
		* @return the list of nbarg
		*/
		vector<string> getArg ();

		virtual void reset ();

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();

	private:
		vector<string> arguments;
		mutex value_m;



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
