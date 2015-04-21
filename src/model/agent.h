#pragma once
#include "value.h"
#include <exception>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <mutex>


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
		 * Reparent to the grand parent agent
		 */
		void reparent ();

		/**
		 * Remove the parent
		 */
		void unparent ();

		/**
		 * Add a value in properties,
		 * @param new_var the new value of properties, his type is pair<string,Value>
		 */
		virtual void setProperty (pair<string,ValuePtr> &&new_var);

		/**
		 * Add a value in properties,
		 * @param new_var the new value of properties, his type is pair<string,Value>
		 */
		virtual void setProperty (pair<string,ValuePtr> &new_var);

		 /**
		 * Get the value of the propertie p
		 * @return the value of propertie p
		 */
		 virtual ValuePtr getProperty(string p);

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
		virtual int compare (ValuePtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a negative number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual int compare (AgentPtr other);

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
		mutex parent_m;
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
