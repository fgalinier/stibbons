/**
  * \file tree.h
  * \brief WorldInterpreter class header.
  * \author Florian Galinier
  * \author Clément Simon
  * \author Adrien Plazas
  * \version 0.4
  * \date 08/04/15
  *
  * Declaration of WorldInterpreter class.
  *
  */

#pragma once

#include "interpreter.h"

#include "tree.h"
#include "syntax-exception.h"
#include "../model/world.h"

namespace stibbons {

	/**
	 * \class WorldInterpreter
	 * \brief Class that will interpret stibbons language.
	 *
	 * This class will parse the standart input, generate a syntaxic tree and interpret it.
	 *
	 * \author Florian Galinier
	 * \author Clément Simon
	 */
	class WorldInterpreter : public virtual Interpreter {
	public:

		/**
		 * Create a new interpreter for a turtle
		 */
		WorldInterpreter() = default;

		/**
		 * Check if the agent is a world and call the interpret for a world
		 * \param agent The agent to run the program on.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return An int equal to 0 if no error has occurred.
		 */
		virtual ValuePtr interpret(InterpreterManager& manager,
		                           AgentPtr agent,
		                           const TreePtr,
		                           TablePtr hashTable);
		/**
		 * Interpret the tree and apply it to the world.
		 * \param agent The agent to run the program on.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return An int equal to 0 if no error has occurred.
		 */
		virtual ValuePtr interpret(InterpreterManager& manager,
		                           WorldPtr agent,
		                           const TreePtr,
		                           TablePtr hashTable);
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
