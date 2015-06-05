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
 * \file stibbons-cli.cpp
 * \brief The Stibbons multi-agent system
 * \author Adrien Plazas
 * \version 1.1
 * \date 05/05/2015
 */

#include "application.h"

#include <QCommandLineParser>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]) {
	stibbons::Application app(argc, argv);

	QCommandLineParser parser;
	parser.setApplicationDescription("The Stibbons headless interpreter");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The Stibbons program file to execute.");

	// Export the model every <seconds> seconds
	parser.addOption(QCommandLineOption(
		QStringList() << "e" << "export",
		"Export the model every <seconds>.",
		"seconds"));

	// Prefix exported files with <prefix>
	parser.addOption(QCommandLineOption(
		QStringList() << "p" << "prefix",
		"Prefix the exported files with <prefix>.",
		"prefix"));

	// Render a PNG for every export
	parser.addOption(QCommandLineOption(
		"png",
		"Render a PNG for every export."));

	// Don't export the model as a JSON file
	parser.addOption(QCommandLineOption(
		"no-json",
		"Don't export the model as a JSON file."));

	// Process the actual command line arguments given by the user
	parser.process(app);

	QStringList args = parser.positionalArguments();
	if (args.size() < 1) {
		cerr << "Please pass a file to run." << endl;
		return 1;
	}

	// Load the program
	auto fileName = args.at(0);
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		cerr << "Couldn't open file " << fileName.toStdString() << endl;
		return 1;
	}
	QTextStream in(&file);
	app.setProgram(in.readAll().toStdString());

	// The the export options
	auto exportInterval = parser.value("export");
	auto prefix = parser.value("prefix");

	bool ok;
	auto seconds = exportInterval.toULong(&ok);
	app.setExportInterval(ok ? seconds : 0);
	app.setExportPrefix(prefix.toStdString());

	app.setRenderPNG(parser.isSet("png"));
	app.setExportJSON(!parser.isSet("no-json"));

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
