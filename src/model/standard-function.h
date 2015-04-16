/**
 * \file standard-function.h
 * \brief Classes implementing standard functions
 * \author Adrien Plazas
 * \version 0.3
 * \date 10/04/2015
 */

#pragma once

#include "function.h"

namespace stibbons {

/**
 * class RandFunction
 *
 *\brief A class returning a random number.
 *
 *\author Adrien Plazas
**/
class RandFunction : public Function {
	public:
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class PrintFunction
 *
 *\brief A class printing on the standard output.
 *
 *\author Adrien Plazas
**/
class PrintFunction : public Function {
	public:
		PrintFunction ();
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class PrintlnFunction
 *
 *\brief A class printing a new line on the standard output.
 *
 *\author Adrien Plazas
**/
class PrintlnFunction : public Function {
	public:
		PrintlnFunction ();
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class TeleportFunction
 *
 *\brief A class teleporting a turtle to another location.
 *
 *\author Adrien Plazas
 **/
class TeleportFunction : public Function {
	public:
		TeleportFunction ();
		virtual Value* exec (Agent* agent, Table* params);
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
