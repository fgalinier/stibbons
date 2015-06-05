/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file application.cpp
 * \brief The Stibbons application
 * \author Adrien Plazas
 * \version 1.1
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
