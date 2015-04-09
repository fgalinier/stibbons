#pragma once

#include "changeable.h"
#include "size.h"
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
		World (Size worldSize, Size zoneSize) throw(domain_error);

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
		 * Get a named breed
		 * @param name the name of the breed
		 * @return the breed
		 */
		Breed* getBreed(string name) throw(out_of_range);

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

		/**
		 * Get the turtles
		 * @return the turtles
		 */
		unordered_set<Turtle *> getTurtles ();

		/**
		 * Get the zone at a given coordinates
		 * @return the zone
		 */
		Zone* getZone (Size& coordinates) throw(domain_error);

		/**
		 * Get the zone at a given point
		 * @return the zone
		 */
		Zone* getZone (Point& point) throw(domain_error);

		/**
		 * Get the world's number of dimensions
		 * @return the world's number of dimensions
		 */
		unsigned getDimensions () const;

		/**
		 * Get the world's size
		 * @return the world's size
		 */
		Size getWorldSize ();

		/**
		 * Get the zones' size
		 * @return the zones' size
		 */
		Size getZoneSize ();

		turtle_id getId ();
		void setId (turtle_id i);

	private:
		Size worldSize;
		Size zoneSize;

		vector<Zone*> zones;

		vector<Line*> lines;

		unordered_map<string, Breed*> namedBreeds;
		unordered_set<Breed*> anonymousBreeds;

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
