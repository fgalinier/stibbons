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
 * \file function.h
 * \brief A class representing a function
 * \author Adrien Plazas
 * \version 1.1
 * \date 10/04/2015
 */

#pragma once

#include "agent.h"
#include "table.h"
#include "value.h"
#include <mutex>
#include <string>
#include <vector>

using namespace std;

namespace stibbons {

/**
 * class Function
 *
 * \brief A class representing a function.
 *
 *\author Adrien Plazas
 */
class Function : public GenericValue<Type::FUNCTION> {
	public:
		/**
		 * Constructor
		 *
		 * \param params the parameters that the function expect to be
		 * executed with
		 */
		Function (vector<string> params = vector<string>());

		/**
		 * Destructor
		 */
		virtual ~Function () = default;

		/**
		 * Execute the function
		 *
		 * \param agent the agent to execute the function on
		 * \param params the parameters to execute the function with
		 * \return the returned value
		 */
		virtual ValuePtr exec (AgentPtr agent, TablePtr params) = 0;

		/**
		 * Execute the function
		 *
		 * \param agent the agent to execute the function on
		 * \param params the parameters to execute the function with
		 * \return the returned value
		 */
		virtual ValuePtr operator() (AgentPtr agent, TablePtr params);

		/**
		 * Get the parameters of the function
		 *
		 * \return the parameters of the function
		 */
		vector<string> getParams ();

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a negative number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * \param other the other value
		 * \return the comparison value of this and the other value
		 */
		virtual double compare (ValuePtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a positive number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * \param other the other value
		 * \return the comparison value of this and the other value
		 */
		virtual double compare (FunctionPtr other);

		/**
		 * Return a string corresponding to the value
		 * \return a string corresponding to the value
		 */
		virtual string toString ();

	protected:
		vector<string> parameters;
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
