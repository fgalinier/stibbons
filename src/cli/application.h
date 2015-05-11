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
#include "../qt/runner.h"
#include "../qt/world-painter.h"

#include <QCoreApplication>
#include <QTimer>

namespace stibbons {

class Application : public QCoreApplication {
	Q_OBJECT

	public:
		Application(int & argc, char ** argv);
		~Application();
		int exec();

		void setProgram(std::string program);
		void setExportInterval(size_t seconds);
		void setExportPrefix(std::string prefix);
		void setRenderPNG(bool value);
		void setExportJSON(bool value);

	public slots:
		void exportModel();

	private slots:
		void error(QString type, QString what);

	private:
		std::string program;
		size_t seconds;
		std::string prefix;
		bool png;
		bool json;

		Runner* runner;
		WorldPainter* painter;
		QTimer* timer;

		void exportModel(QString fileName);
		void exportPNG(QString fileName);
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
