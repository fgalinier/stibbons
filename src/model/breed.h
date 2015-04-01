/**
 * \file breed.h
 * \brief A class representing a breed
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.2
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

class Turtle;
class World;

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
		Breed (Function *function);

		virtual ~Breed ();

		/**
		 * Create and add a new turtle to the breed
		 *
		 * The parent of the turtle will be the breed's world.
		 *
		 * @return a reference to the new turtle
		 */
		Turtle *createTurtle ();

		/**
		 * Create and add a new turtle to the breed
		 *
		 * @param parent the parent of the turtle
		 * @return a reference to the new turtle
		 */
		Turtle *createTurtle (Turtle *parent);

		/**
		 * Remove a turtle from the breed and delete it
		 *
		 * @param turtle the turtle to remove and delete
		 * @throw invalid_argument the breed doesn't contain the turtle
		 */
		void deleteTurtle (Turtle *turtle) throw(invalid_argument);

		/**
		 * Get the turtles
		 *
		 * @return a set containing the turtles of the breed
		 */
		unordered_set<Turtle*> getTurtles ();

		/**
		 * Get the world
		 *
		 * @return the world of the breed
		 */
		World *getWorld ();

		/**
		 * Get the function
		 *
		 * @return the function of the breed
		 */
		Function *getFunction ();

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
		Breed (World *world, Function *function);

		/**
		 * Add a turtle to the breed
		 *
		 * @param turtle the turtle to add
		 */
		void addTurtle (Turtle *turtle);

		/**
		 * Remove a turtle from the breed
		 *
		 * @param turtle the turtle to remove
		 * @throw invalid_argument the breed doesn't contain the turtle
		 */
		void removeTurtle (Turtle *turtle) throw(invalid_argument);

		World *world;
		Function *function;
		mutex value_m;
		unordered_set<Turtle*> turtles;
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
