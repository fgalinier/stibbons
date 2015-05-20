#pragma once
#include "value.h"
#include <exception>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <mutex>
#include "json_spirit.h"
#include "json_spirit_writer_template.h"

using namespace json_spirit;
using namespace std;

namespace stibbons {
/**
 * \class Agent
 *
 * \brief class Agent in stibbons 
 */
class Agent : public Value, public enable_shared_from_this<Agent> {
	public:
		/**
		 * Empty Destructor
		 */
		virtual ~Agent ();

		 /**
		 * Get the parent of the agent
		 * @return the parent of the agent
		 */
		AgentPtr getParent ();

		/**
		 * Get the value of world
		 * @return the value of world
		 */
		virtual WorldPtr getWorld ()=0;

		/**
		 * Reparent to the grand parent agent
		 */
		void reparent ();

		/**
		 * Remove the parent
		 */
		void unparent ();

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
		 * Get the map of the properties
		 * @return the map of properties
		 */
		 virtual unordered_map<string,ValuePtr>* getProperty();

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a positive number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual double compare (ValuePtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a positive number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual double compare (AgentPtr other);

		/**
		 * Export the properties in the object o
		 * @param a reference on an object (jsan spirit type)
		 */
		virtual void exportProperties(Object* o);

		/**
		 * Remove as much references to this agent as possible
		 */
		virtual void destroy();

	protected:
		/**
		 * Empty Constructor
		 * @param parent an unowned reference to the agent's parent
		 */
		Agent (AgentPtr parent = nullptr);

		/**
		 * Initialize the agent
		 */
		void init ();

	private:
		AgentPtr parent;
		unordered_set<AgentPtr> children;

		unordered_map<string,ValuePtr> *properties;

	protected :
		recursive_mutex value_m;
		recursive_mutex parent_m;
};
}
/*
 * Editor modelines-http://www.wireshark.org/tools/modelines.html
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
