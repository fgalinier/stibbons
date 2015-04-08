/**
 * \file tree.h
 * \brief Interpreter class header.
 * \author Florian Galinier
 * \author Clément Simon
 * \version 0.3
 * \date 15/03/15
 *
 * Declaration of Interpreter class.
 *
 */

#pragma once

#include "y.tab.h"
#include "tree.h"
#include "../model/turtle.h"
#include "../model/number.h"
#include "../model/string.h"
#include "../model/boolean.h"
#include "../model/color.h"
#include "../model/nil.h"

namespace stibbons {
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
	private:
		Turtle* turtle;
	public:
		/**
		 * Create a new interpreter
		 * \param turtle The turtle that the stibbons code will affect.
		 */
		Interpreter(Turtle*);
		/**
		 * Parse the standart input and produce the syntaxic tree.
		 * \return The syntaxic tree associated to the standart input.
		 */
		virtual Tree* parse(const char *program) const;
		/**
		 * Interpret the tree and apply it to the turtle.
		 * \param tree The syntaxic tree to interpret.
		 * \param hashTable A hashtable which contain parameters
		 * \return An int equal to 0 if no error has occurred.
		 */
		virtual Value* interpret(const Tree*,
								 unordered_map<std::string,Value*>* hashTable=nullptr) const;
		/**
		 * Create a function from a tree with a
		 * FCT or AGT node.
		 * \param tree A tree with the FCT or AGT root node. 
		 * \return The function corresponding to the tree
		 */
		virtual Function* getFunctionFromTree(const Tree*) const;
		/**
		 * Interpret a function (or function of a breed)
		 * \param fct A function that will be interpreted
		 * \param tree The Tree corresponding to function call
		 * \param hashTable The hashtable that will contains parameters of the function
		 * \param id The name of function for error message
		 * \return The Value returned by the Function fct
		 */
		virtual	Value* interpretFunction(Function*,
										 const Tree*,
										 std::unordered_map<std::string,Value*>*, 
										 std::string) const;
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
