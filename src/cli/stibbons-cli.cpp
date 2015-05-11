/**
 * \file stibbons-cli.cpp
 * \brief The Stibbons multi-agent system
 * \author Adrien Plazas
 * \version 0.5
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
