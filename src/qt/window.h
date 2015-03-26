/**
 * \file window.h
 * \brief The Stibbons main window
 * \author Adrien Plazas
 * \version 0.2
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
		Window(World *world);
		~Window();

	protected:
		void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

	private slots:
		void open();
		void run();
		void halt();
		void about();

	private:
		void createActions();
		void createToolBars();
		void readSettings();
		void writeSettings();

		void loadFile(const QString &fileName);

		QAction *openAct;
		QAction *runAct;
		QAction *haltAct;
		QAction *quitAct;
		QAction *aboutAct;

		World *world;
		WorldView *worldView;

		QToolBar *toolbar;

		std::string program;
		Runner *runner;
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
