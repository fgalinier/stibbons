/**
 * \file application.h
 * \brief The Stibbons application
 * \author Adrien Plazas
 * \version 1.0
 * \date 26/02/2015
 */

#pragma once

#include "../interpreter/interpreter.h"
#include "../model/world.h"

#include <QApplication>

namespace stibbons {
	/**
	 * \class Application
	 * \brief The application itself
	 *
	 * \author Adrien Plazas
	 */

	class Application : private QApplication {
	public:
		/**
		 * Constructor
		 * \param argc the arguments' number
		 * \param argv the arguments' list
		 */
		Application(int & argc, char ** argv);

		/**
		 * Run the application
		 * \return the return state of the application
		 */
		int exec();
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
