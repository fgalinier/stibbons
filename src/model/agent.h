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
class Agent : public Value {
	public:
		/**
		 * Empty Constructor
		 */
		Agent (Agent *parent = nullptr);

		/**
		 * Empty Destructor
		 */
		virtual ~Agent ();

		 /**
		 * Get the parent of the agent
		 * @return the parent of the agent
		 */
		Agent* getParent ();

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
		virtual void setProperty (pair<string,Value*> &new_var);

		 /**
		 * Get the value of the propertie p
		 * @return the value of propertie p
		 */
		 virtual Value* getProperty(string p);

	private:
		Agent *parent;
		unordered_set<Agent *> children;

		unordered_map<string,Value*> *properties;

		void tryDelete (Value* value) throw (domain_error);

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
