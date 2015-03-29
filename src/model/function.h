/**
 * \file function.h
 * \brief A class representing a function
 * \author Julia Bassoumi
 * \version 0.2
 * \date 28/03/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"
#include "../interpreter/tree.h"
#include <iostream>
#include <vector>

namespace stibbons {

/**
 * class Function
 *
 *\brief A class representing a function.
 *
 *\author Julia Bassoumi
**/

class Function : public GenericValue<Type::FUNCTION>, public SimpleValue<Tree>{
	public:
		using SimpleValue<Tree>::SimpleValue;

		/**
		* Constructor
		*/
		Function (vector<Value*> l = vector<Value*>(), Tree arbre = Tree(0,nullptr));

		/**
		* Destructor
		*/
		virtual ~Function ( ) = default;

		/**
		* Set the value of argument
		* @param r the new value of arg
		*/
		void setArg (Value* r);

		/**
		* Get the list of arg
		* @return the list of nbarg
		*/
		vector<Value*> getArg ();

		virtual void reset ();

	private:
		vector<Value*> arguments;



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
