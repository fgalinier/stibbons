/**
 * \file tree.h
 * \brief Interpreter class header.
 * \author Florian Galinier
 * \author Clément Simon
 * \version 1.1
 * \date 15/03/15
 *
 * Declaration of Interpreter class.
 *
 */

#pragma once

#include "y.tab.h"
#include "semantic-exception.h"
#include "tree.h"
#include "../model/turtle.h"
#include "../model/table.h"
#include "../model/number.h"
#include "../model/string.h"
#include "../model/boolean.h"
#include "../model/color.h"
#include "../model/nil.h"
#include <vector>
#include <thread>
#include <condition_variable>

namespace stibbons {

class InterpreterManager;

	/**
	 * \class Interpreter
	 * \brief Class that will interpret stibbons language.
	 *
	 * This class will parse the standart input, generate a syntaxic tree and interpret it.
	 *
	 * \author Florian Galinier
	 * \author Clément Simon
	 */
	class Interpreter {
	public:

		mutex suspendMutex;    /*!< A mutex used to lock the thread when pause is called. */

		bool inPauseFlag;    /*!< A flag which signal if the thread is paused. Useful when export is called
		 * and every thread need to be in pause before exporting model. */


		/**
		 * Create a new interpreter
		 */
		Interpreter() = default;

		/**
		 * Interpret a function (or function of a breed)
		 * \param fct A function that will be interpreted
		 * \param turtle The turtle to run the program on
		 * \param tree The Tree corresponding to function call
		 * \param hashTable The hashtable that will contains parameters of the function
		 * \param id The name of function for error message
		 * \return The Value returned by the Function fct
		 */
		virtual	TablePtr getParams(InterpreterManager& manager,
		                           FunctionPtr,
		                           AgentPtr,
		                           const TreePtr,
		                           TablePtr, 
		                           std::string);

		/**
		 * Interpret a function (or function of a breed)
		 * \param fct A function that will be interpreted
		 * \param turtle The turtle to run the program on
		 * \param tree The Tree corresponding to function call
		 * \param hashTable The hashtable that will contains parameters of the function
		 * \param id The name of function for error message
		 * \return The Value returned by the Function fct
		 */
		virtual	ValuePtr interpretFunction(FunctionPtr,
		                                   AgentPtr,
		                                   TablePtr);

		/**
		 * Create a function from a tree with a
		 * FCT or AGT node.
		 * \param tree A tree with the FCT or AGT root node. 
		 * \return The function corresponding to the tree
		 */

		virtual FunctionPtr getFunctionFromTree(InterpreterManager& manager, const TreePtr);
				
		/**
		 * Get the position of errors
		 * \param tree The syntaxic tree to interpret.
		 * \return The position of the error detected.
		 */
		static yy::position getPosition(const TreePtr);

		/**
		 * Do the affectation operation if token detected is '='
		 * \param agent The agent to run the program on.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return The result of the '=' operation on concerned value.
		 */
		inline ValuePtr affectationOp(InterpreterManager& manager, AgentPtr, TreePtr, TablePtr);

		/**
		 * Do the new operation if token detected is 'NEW'
		 * \param agent The agent to run the program on.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return the newest turtles created by the new operation
		 */
		inline TablePtr newOp(InterpreterManager& manager, AgentPtr, TreePtr, TablePtr);

		/**
		 * Do the calling operation if token detected is 'CALL'
		 * \param agent The agent to run the program on.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return The result of the call operation on concerned value.
		 */
		inline ValuePtr callOp(InterpreterManager& manager, AgentPtr, TreePtr, TablePtr);

		/**
		 * Interpret the tree and apply it to the turtle.
		 * \param agent The agent to run the program on.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return An int equal to 0 if no error has occurred.
		 */
		virtual ValuePtr interpret(InterpreterManager& manager,
		                           AgentPtr agent,
		                           const TreePtr,
		                           TablePtr hashTable=nullptr);
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
