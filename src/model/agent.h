#pragma once
#include "value.h"
#include <exception>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <string>


using namespace std;

namespace stibbons {
/**
 * \class Agent
 *
 * \brief class Agent in stibbons 
 */
class Agent 
{
	public:
		/**
		 * Empty Constructor
		 */
		Agent ();

		/**
		 * Empty Destructor
		 */
		virtual ~Agent ();

		/**
		 * Add a value in properties,
		 * @param new_var the new value of properties, his type is pair<string,Value>
		 */
		virtual void setProperty (pair<string,Value*> &new_var);

		/**
		 * Get the value of properties
		 * @return the value of properties
		 */
		 virtual unordered_map<string,stibbons::Value*> getProperties() const ;
		 
		 /**
		 * Get the value of the propertie p
		 * @return the value of propertie p
		 */
		 virtual Value* getProperty(string p);

	protected:
		unordered_map<string,Value*> *properties;

	private:
		void tryDelete (Value* value) throw (domain_error);
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
