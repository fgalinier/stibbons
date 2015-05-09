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
		static TurtlePtr construct ();

		/**
		 * Create a turtle
		 *
		 */
		static TurtlePtr construct (AgentPtr parent, turtle_id id = 0);

		virtual Type getType() const;

		/**
		 * Add a property
		 * @param key the key of the property
		 * @param value the value of the property
		 */
		virtual void setProperty (string key, ValuePtr value);

		 /**
		 * Get the value of the propertie p
		 * @return the value of propertie p
		 */
		virtual ValuePtr getProperty(string p);

		/**
		 * Set the position of the turtle
		 * @param position the new position of the turtle
		 */
		void setPosition (Point position);

		/**
		 * Get the position of the turtle
		 * @return the position of the turtle
		 */
		Point getPosition ();

		/**
		 * Set the value of angle
		 * @param new_var the new value of angle
		 */
		void setAngle (double new_var);

		/**
		 * Get the value of angle
		 * @return the value of angle
		 */
		double getAngle ();

		/**
		 * Face a point
		 * @param point the point to face
		 */
		void face (Point& point);

		/**
		 * Get the distance to another point
		 * @param other the other point
		 * @return the distance to the other point
		 */
		double getDistanceTo (Point& other);

		/**
		 * Set the value of id
		 * @param new_var the new value of id
		 */
		void setId (turtle_id new_var);

		/**
		 * Get the value of id
		 * @return the value of id
		 */
		turtle_id getId();

		/**
		 * Get the value of world
		 * @return the value of world
		 */
		WorldPtr getWorld ();

		/**
		 * Get the hovered zone
		 * @return the hovered zone
		 */
		ZonePtr getZone ();

		/**
		 * Set the value for an axis
		 * @param axis the axis
		 * @param value the value
		 */
		void setColor (Color color);

		/**
		 * Get the value for an axis
		 * @return a reference to the value for an axis
		 */
		Color& getColor ();

		/**
		 * Get the value for an axis
		 * @return a constant reference to the value for an axis
		 */
		const Color& getColor () const;

		/**
		 * Go forward
		 * @param the distance to go
		 */
		void forward(double dist);

		/**
		 * Turn right at dist degree
		 * @param the degree to turn
		 */
		void turnRight(double angle);

		/**
		 * Turn left at dist degree
		 * @param the degree to turn
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
		 * @return the new child turtle
		 */
		TurtlePtr createChild();

		/**
		 * Special constructor for Breed
		 */
		static TurtlePtr construct (Breed *breed);

		/**
		 * Special constructor for Breed
		 */
		static TurtlePtr construct (TurtlePtr parent);

		void changed ();

		/**
		 * Get the first message receive
		 * @return the first Message 
		 */
		pair<TurtlePtr,ValuePtr> getFirstMessage();

		/**
		 * Get the last message receive
		 * @return the last Message 
		 */
		pair<TurtlePtr,ValuePtr> getLastMessage();

		/**
		 * Send a message to the Turtle t
		 * @param a turtle t and the message
		 */
		void send(TurtlePtr t, ValuePtr);

		/**
		 * Send a message to all the turtle  in t
		 * @param a vector of turtle t and the message
		 */
		void send(vector<TurtlePtr> t, ValuePtr);

		/**
		 * Send a message to all turtles
		 * @param the message a Value
		 */
		void sendAll(ValuePtr);

		/**
		 * Read the first message of the deque and delete it from the deque
		 * @param the etiquette
		 * @return Value, the first message receive
		 */
		pair<TurtlePtr,ValuePtr> recv();

		/**
		 * Check if you have receve some messages
		 * @return the number of message available
		 */
		size_t checkMessage();

		/**
		 * Export turtle's state
		 * @param a string represent the name of his breed, which can not exist
		 * @return a json_spirit object
		 */
		Object exportTurtle(string name = "");

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();

	protected:
		/**
		 * Create a turtle
		 */
		Turtle ();

		/**
		 * Create a turtle
		 *
		 */
		Turtle (AgentPtr parent, turtle_id id = 0);

		/**
		 * Special constructor for Breed
		 */
		Turtle (Breed *breed);

		/**
		 * Special constructor for Breed
		 */
		Turtle (TurtlePtr parent);

		/**
		 * Initialize the world
		 */
		void init ();

	private:
		/**
		 * Add a message to the deque
		 * @param the expediteur and the message
		 */
		void addMessage(TurtlePtr exp, ValuePtr v);

		Point position;

		turtle_id id;
		Breed *breed;
		double angle;
		Color color;
		Line* line;
		deque<pair<TurtlePtr,ValuePtr>> messages;
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
