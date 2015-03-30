/**
 * \file breed.h
 * \brief A class representing a breed
 * \author Julia Bassoumi
 * \version 0.2
 * \date 29/03/2015
 */

#pragma once

#include "agent.h"
#include <string>
#include <vector>
#include "turtle.h"
#include "function.h"
#include <unordered_map>

namespace stibbons {

/**
 * class Breed
 *
 *\brief A class representing a breed.
 *
 *\author Julia Bassoumi
 */

class Breed : public Agent{
	public:
		/**
		* Empty Constructor
		*/
		Breed (Function *function);

		/**
		* Empty Destructor
		*/
//		virtual ~Breed ( );

		/**
		* Add a Turtles object to the turtlesVector List
		*/
		void addTurtles ( Turtle * add_object );

		/**
		* Remove a Turtles object from turtlesVector List
		*/
		void removeTurtles ( Turtle * remove_object );

		/**
		* Get the list of Turtles objects held by turtles
		* @return vector<Turtle *> list of Turtles objects held by turtles
		*/
		vector<Turtle *> getTurtlesList ( );

		/**
		* Get the function
		* @return the function of the breed
		*/
		Function *getFunction ();

	private:
		vector<Turtle*> turtles;
		Function *function;



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
