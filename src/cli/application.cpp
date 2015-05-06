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
	QCoreApplication (argc, argv),
	program(""),
	runner(nullptr)
	{
	setOrganizationName("StibbonsTeam");
	setApplicationName("Stibbons");
	setApplicationVersion("0.5");
}

Application::~Application () {
	if (runner)
		delete runner;
}

int Application::exec () {
	if (runner)
		delete runner;

	try {
		runner = new Runner(program);
	}
	catch (SemanticException e) {
		error("Semantic error", QString(e.what()));
		return 1;
	}
	catch (SyntaxException e) {
		error("Syntax error", QString(e.what()));
		return 1;
	}
	catch (exception e) {
		error("Unknown error", QString(e.what()));
		return 1;
	}

	connect(runner, SIGNAL(error(QString,QString)),
		    this, SLOT(error(QString,QString)));

	runner->start();

	return QCoreApplication::exec();
}

void Application::error(QString type, QString what) {
	cerr << type.toStdString() << ": " << what.toStdString() << endl;
}

void Application::setProgram (std::string program) {
	this->program = program;
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
