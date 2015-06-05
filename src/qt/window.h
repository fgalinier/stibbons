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
 * \file window.h
 * \brief The Stibbons main window
 * \author Adrien Plazas
 * \version 1.1
 * \date 26/02/2015
 */

#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QtWidgets>
#include <QApplication>
#include <QtGui>
#include <QTextEdit>
#include <QFile>
#include <QString>
#include <QTextCursor>
#include <QTextStream> 
#include "../model/world.h"
#include "world-view.h"
#include "runner.h"
#include "stibbons-editor.h"
#include "stibbons-highlighter.h"

class QAction;
class QMenu;
using namespace std;
namespace stibbons {

	/**
	 * \class Window
	 * \brief The window of Qt application.
	 *
	 * \author Adrien Plazas
	 */
	class Window : public QMainWindow {
		Q_OBJECT

	public:
		/**
		 * Constructor
		 */
		Window();

		/**
		 * Destructor
		 */
		~Window();

	protected:
		void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

		public slots:
			void open();
			void reset();
			void run();
			void rerun();
			void halt();
			void exportModel();
			void exportModel(QString fileName);
			void about();
			void updateInterpreterWaitTime(int waitTime);
			void save();
			void saveUnder();

			void error(QString type, QString what);

			private slots:
				void nextTab();
				void previousTab();

	signals :
				void change();

	private:
				void createActions();
				void createToolBars();
				void readSettings();
				void writeSettings();

				void loadFile(const QString &fileName);
				void loadProgram();

				void updateToolbar();

				void createTab(QScrollArea *t);

				void loadText(QString fileName);

				void updatePrint(QScrollArea* t);

				QAction *openAct;
				QAction *resetAct;
				QAction *runAct;
				QAction *rerunAct;
				QAction *haltAct;
				QAction *quitAct;
				QAction *aboutAct;
				QAction *exportAct;
				QAction *saveAct;
				QAction *saveUnderAct;

				WorldView *worldView;

				QToolBar *toolbar;
				QSlider* slider;

				QTabWidget *tab;
				QWidget *print;
				QWidget *code;
				StibbonsEditor *textArea;
				StibbonsHighlighter *highlighter;

				Runner *runner;

				std::string program;
				QString openFileName;

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
