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
 * \file user-function.h
 * \brief A class representing a user defined function
 * \author Adrien Plazas
 * \version 1.1
 * \date 10/04/2015
 */

#pragma once

#include "function.h"

#include "../interpreter/interpreter-manager.h"
#include "../interpreter/tree.h"

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
		 * \param manager the interpreter manager
		 * \param tree the syntactic tree of the function
		 * \param params the parameters that the function expect to be
		 * executed with
		 */
		UserFunction (InterpreterManager& manager, TreePtr tree, vector<string> params = vector<string>());

		/**
		 * Constructor
		 *
		 * \param tree the syntactic tree of the function
		 * \param params the parameters that the function expect to be
		 * executed with
		 */
		UserFunction (TreePtr tree, vector<string> params = vector<string>());

		/**
		* Destructor
		*/
		virtual ~UserFunction () = default;

		/**
		 * Execute the function
		 *
		 * \param agent the agent to execute the function on
		 * \param params the parameters to execute the function with
		 * \return the returned value
		 */
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);

	private:
		InterpreterManager* manager;
		TreePtr tree;
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
