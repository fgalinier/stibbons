/**
 * \file standard-function.h
 * \brief Classes implementing standard functions
 * \author Adrien Plazas
 * \author Florian Galinier
 * \version 1.1
 * \date 10/04/2015
 */

#pragma once

#include "function.h"
#include "singleton.h"

namespace stibbons {

/**
 * class TypeOfFunction
 *
 *\brief A class returning the type of a value.
 *
 *\author Adrien Plazas
**/
class TypeOfFunction : public Function, public Singleton<TypeOfFunction> {
	friend Singleton<TypeOfFunction>;
	protected:
		TypeOfFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class RandFunction
 *
 *\brief A class returning a random number.
 *
 *\author Adrien Plazas
**/
class RandFunction : public Function, public Singleton<RandFunction> {
	friend Singleton<RandFunction>;
	protected:
		RandFunction () = default;
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class RandomFunction
 *
 *\brief A class returning a random number in a range.
 *
 *\author Florian Galinier
**/
class RandomFunction : public Function, public Singleton<RandomFunction> {
	friend Singleton<RandomFunction>;
	protected:
		RandomFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class PrintFunction
 *
 *\brief A class printing on the standard output.
 *
 *\author Adrien Plazas
**/
class PrintFunction : public Function, public Singleton<PrintFunction> {
	friend Singleton<PrintFunction>;
	protected:
		PrintFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class PrintlnFunction
 *
 *\brief A class printing a new line on the standard output.
 *
 *\author Adrien Plazas
**/
class PrintlnFunction : public Function, public Singleton<PrintlnFunction> {
	friend Singleton<PrintlnFunction>;
	protected:
		PrintlnFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class TeleportFunction
 *
 *\brief A class teleporting a turtle to another location.
 *
 *\author Adrien Plazas
 **/
class TeleportFunction : public Function, public Singleton<TeleportFunction> {
	friend Singleton<TeleportFunction>;
	protected:
		TeleportFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class SendFunction
 *
 *\brief A class sending a message from a turtle to another.
 *
 *\author Adrien Plazas
 **/
class SendFunction : public Function, public Singleton<SendFunction> {
	friend Singleton<SendFunction>;
	protected:
		SendFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class InboxFunction
 *
 *\brief A class returning the number of unread messages.
 *
 *\author Adrien Plazas
 **/
class InboxFunction : public Function, public Singleton<InboxFunction> {
	friend Singleton<InboxFunction>;
	protected:
		InboxFunction () = default;
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class DistanceToFunction
 *
 *\brief A class returning the distance to another turtle.
 *
 *\author Adrien Plazas
 **/
class DistanceToFunction : public Function, public Singleton<DistanceToFunction> {
	friend Singleton<DistanceToFunction>;
	protected:
		DistanceToFunction ();
	public:
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class FaceFunction
 *
 *\brief A class making a turtle face another.
 *
 *\author Adrien Plazas
 **/
class FaceFunction : public Function, public Singleton<FaceFunction> {
	friend Singleton<FaceFunction>;
	protected:
		FaceFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class InRadiusFunction
 *
 *\brief A class making a turtle face another.
 *
 *\author Adrien Plazas
 **/
class InRadiusFunction : public Function, public Singleton<InRadiusFunction> {
	friend Singleton<InRadiusFunction>;
	protected:
		InRadiusFunction ();
	public:
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class AskZonesFunction
 *
 *\brief A class applying a function to every zone.
 *
 *\author Adrien Plazas
 **/
class AskZonesFunction : public Function, public Singleton<AskZonesFunction> {
	friend Singleton<AskZonesFunction>;
	protected:
		AskZonesFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
};

/**
 * class SizeFunction
 *
 *\brief A class that return an array size.
 *
 *\author Florian Galinier
**/
class SizeFunction : public Function, public Singleton<SizeFunction> {
	friend Singleton<SizeFunction>;
	protected:
		SizeFunction ();
	public:
		/**
		 * Execute the function 
		 *\param  an Agent pointer to execute on
		 *\param a Table pointer with the parameters
		 **/
		virtual ValuePtr exec (AgentPtr agent, TablePtr params);
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
