/**
 * \file window.h
 * \brief The Stibbons main window
 * \author Adrien Plazas
 * \version 0.5
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
#include <QTextStream> 
#include "../model/world.h"
#include "world-view.h"
#include "runner.h"
#include "stibbons-editor.h"
#include "stibbons-highlighter.h"

class QAction;
class QMenu;

namespace stibbons {

class Window : public QMainWindow {
	Q_OBJECT

	public:
		Window();
		~Window();

	protected:
		void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

	private slots:
		void open();
		void reset();
		void run();
		void halt();
		void exportModel();
		void exportModel(QString fileName);
		void about();
		void updateInterpreterWaitTime(int waitTime);
		void save();

		void error(QString type, QString what);

	private:
		void createActions();
		void createToolBars();
		void readSettings();
		void writeSettings();

		void loadFile(const QString &fileName);
		void loadProgram();

		void updateToolbar();

		void createOnglet(QScrollArea *t);

		void loadText(QString fileName);

		QAction *openAct;
		QAction *resetAct;
		QAction *runAct;
		QAction *haltAct;
		QAction *quitAct;
		QAction *aboutAct;
		QAction *exportAct;
		QAction *saveAct;

		WorldView *worldView;

		QToolBar *toolbar;
		QSlider* slider;

		QTabWidget *onglets;
		StibbonsEditor *zoneTexte;
		StibbonsHighlighter *highlighter;

		Runner *runner;

		std::string program;
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
