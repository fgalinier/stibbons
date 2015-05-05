/**
 * \file application.cpp
 * \brief The Stibbons headless application
 * \author Adrien Plazas
 * \version 0.5
 * \date 05/05/2015
 */

#include "application.h"

namespace stibbons {

Application::Application (int & argc, char ** argv) :
	QCoreApplication (argc, argv)
	{
	setOrganizationName("StibbonsTeam");
	setApplicationName("Stibbons");
}

int Application::exec () {
	// Analyser la ligne de commande

	/* Options :
	stibbons-cli [OPTIONS] [FILE]
	[OPTIONS]
		-e=temps --export=temps exporter le modèle toutes les x secondes
		-o --output préfixe des fichiers générés (auquel s'ajoute le temps et le format)
		-r --render rendre le monde à chaque export
		-f --format paramètre le format de rendu (svg, png...)
	[FILE] un programme Stibbons
	*/

	return QCoreApplication::exec();
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
