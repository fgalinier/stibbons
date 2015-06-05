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
 * \brief The Stibbons headless application
 * \author Adrien Plazas
 * \version 1.1
 * \date 05/05/2015
 */

#include "application.h"

#include <QFile>
#include <QDateTime>

namespace stibbons {

Application::Application (int & argc, char ** argv) :
	QCoreApplication (argc, argv),
	program(""),
	seconds(0),
	prefix(""),
	png(false),
	json(true),
	runner(nullptr),
	painter(nullptr),
	timer(nullptr)
	{
	setOrganizationName("StibbonsTeam");
	setApplicationName("Stibbons");
	setApplicationVersion("1.1");
}

Application::~Application () {
	if (runner)
		delete runner;

	if (painter)
		delete painter;

	if (timer)
		delete timer;
}

int Application::exec () {
	if (runner)
		delete runner;

	if (painter)
		delete painter;

	if (timer)
		delete timer;

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

	if (seconds != 0) {
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(exportModel()));
		timer->setSingleShot(false);
		timer->start(seconds*1000);
	}

	painter = new WorldPainter(runner->getWorld());

	runner->start();

	return QCoreApplication::exec();
}

void Application::error(QString type, QString what) {
	cerr << type.toStdString() << ": " << what.toStdString() << endl;
}

void Application::setProgram (std::string program) {
	this->program = program;
}

void Application::setExportInterval (size_t seconds) {
	this->seconds = seconds;
}

void Application::setExportPrefix (std::string prefix) {
	this->prefix = prefix;
}

void Application::setRenderPNG (bool value) {
	png = value;
}

void Application::setExportJSON (bool value) {
	json = value;
}

void Application::exportModel() {
	if (runner) {
		runner->halt();

		auto time = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
		auto timeStampedPrefix = QString(prefix.c_str()) + "-" + time;

		if (json)
			exportModel(timeStampedPrefix + ".json");
		if (png)
			exportPNG(timeStampedPrefix + ".png");

		runner->start();
	}
}

void Application::exportModel(QString fileName) {
	if (runner) {
		QFile file(fileName);
		if (!file.open(QFile::WriteOnly | QFile::Text))
			return;

		auto exported = runner->exportModel();

		file.write(exported.c_str());
	}
}

void Application::exportPNG(QString fileName) {
	if (runner && painter) {
		auto world = runner->getWorld();
		auto ws = world ? world->getSize() : Size();
		auto image = QImage(ws.getValue(0), ws.getValue(1), QImage::Format_RGB32);

		QPainter p(&image);
		painter->paint(p);

		image.save(fileName, "PNG");
	}
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
