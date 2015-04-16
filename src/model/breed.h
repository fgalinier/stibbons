/**
 * \file breed.h
 * \brief A class representing a breed
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.3
 * \date 29/03/2015
 */

#pragma once

#include "agent.h"
#include "function.h"
#include "turtle.h"
#include "world.h"
#include <mutex>

#include<mutex>
#include <string>
#include <unordered_set>

namespace stibbons {

/**
 * class Breed
 *
 *\brief A class representing a breed.
 *
 *\author Julia Bassoumi, Adrien Plazas
 */
class Breed {
	friend World;
	friend Turtle;

	public:
		/**
		 * Create a breed from a function.
		 *
		 * The breed will own the function and destroy it when it is
		 * deleted.
		 *
		 * @param function the function of the breed
		 */
		Breed (FunctionPtr function);

		virtual ~Breed () = default;

		/**
		 * Create and add a new turtle to the breed
		 *
		 * The parent of the turtle will be the breed's world.
		 *
		 * @return a reference to the new turtle
		 */
		TurtlePtr createTurtle ();

		/**
		 * Create and add a new turtle to the breed
		 *
		 * @param parent the parent of the turtle
		 * @return a reference to the new turtle
		 */
		TurtlePtr createTurtle (TurtlePtr parent);

		/**
		 * Get the turtles
		 *
		 * @return a set containing the turtles of the breed
		 */
		unordered_set<TurtlePtr> getTurtles ();

		/**
		 * Get the world
		 *
		 * @return the world of the breed
		 */
		WorldPtr getWorld ();

		/**
		 * Get the function
		 *
		 * @return the function of the breed
		 */
		FunctionPtr getFunction ();

	private:
		/**
		 * Create a breed from a world and a function.
		 *
		 * Special constructor for World
		 *
		 * The breed will own the function and destroy it when it is
		 * deleted.
		 *
		 * @param world the world of the breed
		 * @param function the function of the breed
		 */
		Breed (WorldPtr world, FunctionPtr function);

		/**
		 * Add a turtle to the breed
		 *
		 * @param turtle the turtle to add
		 */
		void addTurtle (TurtlePtr turtle);

		/**
		 * Remove a turtle from the breed
		 *
		 * @param turtle the turtle to remove
		 * @throw invalid_argument the breed doesn't contain the turtle
		 */
		void removeTurtle (TurtlePtr turtle) throw(invalid_argument);

		WorldPtr world;
		FunctionPtr function;
		mutex value_m;
		unordered_set<TurtlePtr> turtles;
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
