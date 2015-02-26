/**
 * \file stibbons.cpp
 * \brief The Stibbons application.
 * \author Adrien Plazas
 * \version 0.1
 * \date 26/02/2015
 *
 * The Stibbons multi-agent system development environment.
 *
 */

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	app.setOrganizationName("StibbonsTeam");
	app.setApplicationName("Stibbons");

	return app.exec();
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
