/**
 * \file user-function.h
 * \brief A class representing a user defined function
 * \author Adrien Plazas
 * \version 0.3
 * \date 10/04/2015
 */

#pragma once

#include "function.h"

//#include "value.h"
#include "../interpreter/tree.h"
//#include <iostream>
//#include <vector>
//#include <string>
//#include <mutex>

namespace stibbons {

/**
 * class UserFunction
 *
 *\brief A class representing a user defined function.
 *
 *\author Adrien Plazas
**/
class UserFunction : public Function {
	public:
		/**
		 * Constructor
		 *
		 * @param tree the syntactic tree of the function
		 * @param params the parameters that the function expect to be
		 * executed with
		 */
		UserFunction (Tree* tree, vector<string> params = vector<string>());

		/**
		* Destructor
		*/
		virtual ~UserFunction () = default;

		/**
		 * Execute the function
		 *
		 * @param agent the agent to execute the function on
		 * @param params the parameters to execute the function with
		 * @return the returned value
		 */
		virtual Value* exec (Agent* agent, Table* params);

	private:
		Tree* tree;
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
