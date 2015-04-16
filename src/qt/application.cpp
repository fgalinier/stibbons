/**
 * \file application.cpp
 * \brief The Stibbons application
 * \author Adrien Plazas
 * \version 0.3
 * \date 26/02/2015
 */

#include "application.h"
#include "../model/turtle.h"

#include "window.h"

namespace stibbons {

Application::Application (int & argc, char ** argv) : QApplication (argc, argv) {
	setOrganizationName("StibbonsTeam");
	setApplicationName("Stibbons");
	setWindowIcon(QIcon(":/images/stibbons.svg"));
}

int Application::exec () {
	Window win;
	win.show();

	return QApplication::exec();
}

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
