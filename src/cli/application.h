/**
 * \file application.h
 * \brief The Stibbons headless application
 * \author Adrien Plazas
 * \version 0.5
 * \date 05/05/2015
 */

#pragma once

#include "../interpreter/interpreter.h"
#include "../model/world.h"

#include <QCoreApplication>

namespace stibbons {

class Application : private QCoreApplication {
	public:
		Application(int & argc, char ** argv);
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
