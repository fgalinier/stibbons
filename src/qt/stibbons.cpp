/**
 * \file stibbons.cpp
 * \brief The Stibbons multi-agent system
 * \author Adrien Plazas
 * \version 0.4
 * \date 26/02/2015
 */

#include "application.h"

int main(int argc, char *argv[]) {
	// Must be called outside of any namespace
	Q_INIT_RESOURCE(stibbons);

	stibbons::Application app(argc, argv);
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
