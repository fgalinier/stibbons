/**
 * \file interpreter-manager.h
 * \brief InterpreterManager class header.
 * \author Florian Galinier
 * \author Adrien Plazas
 * \version 0.5
 * \date 30/04/15
 */

#pragma once

#include "interpreter.h"
#include "tree.h"
#include "syntax-exception.h"

#include "../model/world.h"

#include <mutex>
#include <thread>
#include <vector>

using namespace std;

namespace stibbons {

	class Interpreter;

	class exit_requested_exception : exception {};

	/**
	 * \class InterpreterManager
	 * \brief Class that will interpret stibbons language.
	 *
	 * This class will parse the standart input, generate a syntaxic tree
	 * and interpret it.
	 *
	 * \author Florian Galinier
	 * \author Adrien Plazas
	 */
	class InterpreterManager {
	private:
		WorldPtr world;
		TreePtr tree;

		vector<pair<shared_ptr<Interpreter>, shared_ptr<thread>>> interpreters;

		std::function<void(string,string)> errorCallback;

		size_t waitTime;    /*!< A size_t to control the speed.*/
		mutex stopMutex;    /*!< A mutex to stop everything when stop button is pressed*/
		bool exitFlag;	    /*!< A flag to signal when stop button is pressed*/
		

		/**
		 * Run the interpreter with the parsed program.
		 */
		void interpret(shared_ptr<Interpreter> interpreter,
		               FunctionPtr function,
		               AgentPtr agent,
		               TablePtr params);

		void errorsOccured (string type, string what);

		void stop ();

	public:
		static bool suspendFlag; /*!< A boolean to signal when pause button is pressed*/
		static condition_variable resumeCond; /*!< A condition variable to control pause with all interpreters threads*/

		/**
		 * Create an interpreter manager
		 *
		 * It parse a Stibbons program, store its syntactic tree and
		 * return the Wolrd generated by this tree.
		 *
		 * \param program The Stibbons program to parse.
		 */
		InterpreterManager(std::string program) throw(InterpreterException);

		virtual ~InterpreterManager();

		static inline yy::position getPosition(const TreePtr tree);

		/**
		 * Get the world.
		 *
		 * \return The world associated to given program.
		 */
		virtual WorldPtr getWorld();

		void onErrors (std::function<void(string,string)> callback);

		/**
		 * Run the interpreter with the parsed program.
		 */
		virtual void run();

		virtual void wait();

		virtual void checkExit() throw(exit_requested_exception);

		/**
		 * Set the wait time used to slow down the interpretations.
		 *
		 * \param waitTime the waited time
		 */
		virtual void setWaitTime(size_t waitTime);


		virtual void checkHalt();

		/**
		 * Halt the execution of the interpreter.
		 */
		virtual void halt();

		/**
		 * Un-halt the execution of the interpreter.
		 */
		virtual void unhalt();

		/**
		 * Run the interpreter with the parsed program.
		 */
		template<class I>
			void interpret_async(FunctionPtr function,
								 AgentPtr agent,
								 TablePtr params) {
			auto i = make_shared<I>();

			auto t = make_shared<thread>(&InterpreterManager::interpret,
				                         this,
				                         i,
				                         function,
				                         agent,
				                         params);

			interpreters.push_back(pair<shared_ptr<Interpreter>, shared_ptr<thread>>(i, t));
		}
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
