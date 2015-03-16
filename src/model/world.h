#pragma once

#include "changeable.h"
#include "zone.h"
#include "turtle.h"
#include "line.h"

//#include <cstdarg>
#include <vector>
//#include <stdlib.h>

using namespace std;

namespace stibbons {

class Turtle;

typedef unsigned long turtle_id;

/**
 * \class World
 *
 * \brief A world consisting of zones, breeds, turtles and lines.
 *
 * \author Julia Bassoumi
 */
class World : public Changeable {
	public:
		/**
		 * Create a world
		 */
		World (unsigned width, unsigned height);

		/**
		 * Empty Destructor
		 */
		~World ();

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

		turtle_id getId () const;
		void setId (turtle_id i);

	private:
		unsigned width;
		unsigned height;
		vector<Zone*> zones;

		vector<Line*> lines;

		vector<Turtle*> turtles;
		turtle_id id;
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
