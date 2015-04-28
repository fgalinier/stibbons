/**
 * \file window.h
 * \brief The Stibbons main window
 * \author Adrien Plazas
 * \version 0.4
 * \date 26/02/2015
 */

#pragma once

#include <QMainWindow>

#include "../model/world.h"
#include "world-view.h"
#include "runner.h"

class QAction;
class QMenu;
class QPlainTextEdit;

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
		void next();
		void about();
		void updateInterpreterWaitTime(int waitTime);

	private:
		void createActions();
		void createToolBars();
		void readSettings();
		void writeSettings();

		void loadFile(const QString &fileName);
		void loadProgram();

		QAction *openAct;
		QAction *resetAct;
		QAction *runAct;
		QAction *haltAct;
		QAction *nextAct;
		QAction *quitAct;
		QAction *aboutAct;

		WorldView *worldView;

		QToolBar *toolbar;

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
