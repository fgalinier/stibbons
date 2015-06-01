/**
 * \file application.h
 * \brief The Stibbons headless application
 * \author Adrien Plazas
 * \version 1.1
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

	/**
	 * \class Application
	 * \brief The headless application
	 *
	 * \author Adrien Plazas
	 */
	class Application : public QCoreApplication {
		Q_OBJECT

	public:
		/**
		 * Constructor
		 * \param argc the arguments' number
		 * \param argv the arguments' list
		 */
		Application(int & argc, char ** argv);

		/**
		 * Destructor
		 */
		~Application();

		/**
		 * Run the application
		 * \return the return state of the application
		 */
		int exec();

		/**
		 * Set the program to execute
		 * \param program the program to execute
		 */
		void setProgram(std::string program);

		/**
		 * Set the export interval
		 * \param second the interval between two exports
		 */
		void setExportInterval(size_t seconds);

		/**
		 * Set the export prefix
		 * \param prefix the prefix to determine what need to be exported
		 */
		void setExportPrefix(std::string prefix);

		/**
		 * Set if the png image is rendered
		 * \param value a boolean to determine the export or not
		 */
		void setRenderPNG(bool value);

		/**
		 * Set if the JSON text is exported
		 * \param value a boolean to determine the export or not
		 */
		void setExportJSON(bool value);

		public slots:

			/**
			 * Method called to export
			 */
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
