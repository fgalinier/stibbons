/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file turtle.h
 * \brief The Turtle class header.
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
 * \date 08/04/2015
 */
#pragma once

#include "changeable.h"
#include "color.h"
#include "point.h"
#include "world.h"
#include "zone.h"
#include "line.h"
#include "agent.h"
#include "breed.h"
#include "value.h"
#include <future>
#include <cmath>
#include <string>
#include <fstream>
#include <deque>
#include <stdexcept>
#include <system_error>
#include <unordered_map>
#include <mutex>
#include "json_spirit.h"
#include "json_spirit_writer_template.h"

using namespace json_spirit;
using namespace std;

namespace stibbons {

class World;
class Zone;
typedef std::shared_ptr<World> WorldPtr;
class Breed;

typedef unsigned long turtle_id;

/**
 *\class Turtle
 *
 *\brief class Turtle stibbons
 *
 *\author Julia Bassoumi
 */
class Turtle : public Agent {
	friend Breed;

	public:
		/**
		 * Create a turtle
		 */
		static TurtlePtr construct (Breed *breed = nullptr);

		/**
		 * Construct a turtle
		 * \param breed the turtle's breed
		 * \param parent a turtle who create the current turtle
		 * \param id the id of the turtle
		 */
		static TurtlePtr construct (Breed *breed, AgentPtr parent, turtle_id id = 0);

		virtual Type getType() const;

		/**
		 * Add a property
		 * \param key the key of the property
		 * \param value the value of the property
		 */
		virtual void setProperty (string key, ValuePtr value);

		 /**
		 * Get the value of the propertie p
		 * \return the value of propertie p
		 */
		virtual ValuePtr getProperty(string p);

		/**
		 * Set the position of the turtle
		 * \param position the new position of the turtle
		 */
		void setPosition (Point position);

		/**
		 * Get the position of the turtle
		 * \return the position of the turtle
		 */
		Point getPosition ();

		/**
		 * Set the value of angle
		 * \param new_var the new value of angle
		 */
		void setAngle (double new_var);

		/**
		 * Get the value of angle
		 * \return the value of angle
		 */
		double getAngle ();

		/**
		 * Face a point
		 * \param point the point to face
		 */
		void face (Point& point);

		/**
		 * Get the distance to another point
		 * \param other the other point
		 * \return the distance to the other point
		 */
		double getDistanceTo (Point& other);

		/**
		 * Set the value of id
		 * \param new_var the new value of id
		 */
		void setId (turtle_id new_var);

		/**
		 * Get the value of id
		 * \return the value of id
		 */
		turtle_id getId();

		/**
		 * Get the value of world
		 * \return the value of world
		 */
		WorldPtr getWorld ();

		/**
		 * Get the hovered zone
		 * \return the hovered zone
		 */
		ZonePtr getZone ();

		/**
		 * Set the value for an axis
		 * \param axis the axis
		 * \param value the value
		 */
		void setColor (Color color);

		/**
		 * Get the value for an axis
		 * \return a reference to the value for an axis
		 */
		Color& getColor ();

		/**
		 * Get the value for an axis
		 * \return a constant reference to the value for an axis
		 */
		const Color& getColor () const;

		/**
		 * Go forward
		 * \param the distance to go
		 */
		void forward(double dist);

		/**
		 * Turn right at dist degree
		 * \param the degree to turn
		 */
		void turnRight(double angle);

		/**
		 * Turn left at dist degree
		 * \param the degree to turn
		 */
		void turnLeft(double angle);

		/**
		 * Let a trace on the map behind the turtle
		 */
		void penDown() throw (future_error);

		/**
		 * Stop to trace on the map behind the turtle
		 */
		void penUp() throw (future_error);

		/**
		 * Create a child turtle
		 *
		 * Create a new turtle whose parent is this turtle, and whose
		 * breed and color are this turtle's breed and color.
		 *
		 * \return the new child turtle
		 */
		TurtlePtr createChild();

		/**
		 * Special constructor for Breed
		 */
		static TurtlePtr construct (TurtlePtr parent);

		void changed ();

		/**
		 * Get the first message receive
		 * \return the first Message 
		 */
		pair<TurtlePtr,ValuePtr> getFirstMessage();

		/**
		 * Get the last message receive
		 * \return the last Message 
		 */
		pair<TurtlePtr,ValuePtr> getLastMessage();

		/**
		 * Send a message to the Turtle t
		 * \param t a turtle
		 * \param v the message to send
		 */
		void send(TurtlePtr t, ValuePtr v);

		/**
		 * Send a message to all the turtle in t
		 * \param t a vector of turtle
		 * \param v the message to send
		 */
		void send(vector<TurtlePtr> t, ValuePtr v);

		/**
		 * Send a message to all turtles
		 * \param the message a Value
		 */
		void sendAll(ValuePtr);

		/**
		 * Read the first message of the deque and delete it from the deque
		 * \param the etiquette
		 * \return Value, the first message receive
		 */
		pair<TurtlePtr,ValuePtr> recv();

		/**
		 * Check if you have receve some messages
		 * \return the number of message available
		 */
		size_t checkMessage();

		/**
		 * Export turtle's state
		 * \param a string represent the name of his breed, which can not exist
		 * \return a json_spirit object
		 */
		Object exportTurtle(string name = "");

		/**
		 * Return a string corresponding to the value
		 * \return a string corresponding to the value
		 */
		virtual string toString ();

		/**
		 * Kill a turtle
		 */
		void die ();

		/**
		 * Remove as much references to this agent as possible
		 */
		virtual void destroy();

	protected:
		/**
		 * Create a turtle with breed
		 * \param breed the turtle's breed
		 */
		Turtle (Breed *breed);

		/**
		 * Create a turtle
		 * \param breed the turtle's breed
		 * \param parent a turtle who create the current turtle
		 * \param id the id of the turtle
		 */
		Turtle (Breed *breed, AgentPtr parent, turtle_id id = 0);

		/**
		 * Special constructor for Breed
		 * \param parent a turtle who create the current turtle
		 */
		Turtle (TurtlePtr parent);

		/**
		 * Initialize the world
		 */
		void init ();

	private:
		/**
		 * Add a message to the deque
		 * \param exp the sender
		 * \param v the message
		 */
		void addMessage(TurtlePtr exp, ValuePtr v);

		Point position;

		turtle_id id;
		Breed *breed;
		double angle;
		Color color;
		Line* line;
		deque<pair<TurtlePtr,ValuePtr>> messages;

		inline bool getBounce(Point& start, Point& end, Point& outCrossing, double& outRemainingDist, double& outAngle);
		inline bool isBoundCrossed(Point& start, Point& end, size_t axis, double lower, double upper, Point& outCrossing, double& outRemainingDist);
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
