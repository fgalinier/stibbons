#pragma once

#include "changeable.h"
#include "zone.h"
#include "turtle.h"
#include "line.h"
#include "breed.h"
#include "function.h"

//#include <cstdarg>
#include <vector>
#include <mutex>
//#include <stdlib.h>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

using namespace std;

namespace stibbons {

class Turtle;
class Breed;
class Function;

typedef unsigned long turtle_id;

/**
 * \class World
 *
 * \brief A world consisting of zones, breeds, turtles and lines.
 *
 * \author Julia Bassoumi
 */
class World : public Changeable, public Agent {
	public:
		/**
		 * Create a world
		 */
		World (unsigned width, unsigned height);

		/**
		 * Empty Destructor
		 */
		~World ();

		virtual Type getType() const;

		/**
		 * Add a line
		 */
		void addLine (Line* add_object);

		/**
		 * Get the lines
		 * @return the lines
		 */
		vector<Line*> getLines ();

		/**
		 * Add a turtle
		 */
		void addTurtle (Turtle* add_object);

		/**
		 * Remove a turtle
		 */
		void removeTurtle (Turtle* remove_object);

		/**
		 * Get the turtles
		 * @return the turtles
		 */
		vector<Turtle*> getTurtles ();

		/**
		 * Create and add a new named breed
		 * @param function the function of the breed
		 * @param name the name of the breed
		 * @return a reference to the new breed
		 */
		Breed* createBreed (Function& function, string name) throw(invalid_argument);

		/**
		 * Create and add a new anonymous breed
		 * @param function the function of the breed
		 * @return a reference to the new breed
		 */
		Breed* createBreed (Function& function);

		turtle_id getId () const;
		void setId (turtle_id i);

	private:
		unsigned width;
		unsigned height;
		vector<Zone*> zones;

		vector<Line*> lines;

		unordered_map<string, Breed*> namedBreeds;
		unordered_set<Breed*> anonymousBreeds;

		vector<Turtle*> turtles;
		turtle_id id;

		mutex value_m;
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
