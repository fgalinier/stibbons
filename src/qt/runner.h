/**
 * \file runner.h
 * \brief The Runner class header
 * \author Adrien Plazas
 * \version 1.1
 * \date 05/05/2015
 */

#pragma once

#include <QThread>

#include <mutex>
#include <string>

#include "../interpreter/interpreter-manager.h"

namespace stibbons {
	
	/**
	 * \class Runner
	 * \brief Bridge between the interpreter and Qt application
	 *
	 * \author Adrien Plazas
	 */
	class Runner : public QThread {
		Q_OBJECT

	public:
		/**
		 * Constructor
		 * \param program the code to interpret
		 */
		Runner(std::string& program);

		/**
		 * Destructor
		 */
		~Runner();

		/**
		 * Get the current world
		 * \return the current world
		 */
		WorldPtr getWorld();

		/**
		 * Start the QThread
		 */
		void start();

		/**
		 * Run the program
		 */
		void run();

		/**
		 * Halt the program
		 */
		void halt();

		/**
		 * Export the model
		 * \return a json string
		 */
		std::string exportModel();

		/**
		 * Return true if the program is running
		 * \return a boolean corresponding to the program's state
		 */
		bool isRunning();

	signals:
		/**
		 * Signal when an error occured
		 *
		 * \param type the error type
		 * \param what the error text
		 */
		void error(QString type, QString what);

		public slots:
			/**
			 * Set the wait time used to slow down the interpretations.
			 *
			 * \param waitTime the waited time
			 */
			void setWaitTime(size_t waitTime);

	private:
			void unhalt();

			InterpreterManager* manager;
			bool started;
			bool running;
			std::recursive_mutex haltMutex;
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
