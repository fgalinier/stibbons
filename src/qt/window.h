/**
 * \file window.h
 * \brief The Stibbons main window
 * \author Adrien Plazas
 * \version 0.1
 * \date 26/02/2015
 */

#pragma once

#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;

namespace stibbons {

class Window : public QMainWindow {
	Q_OBJECT

	public:
		Window();

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

		QAction *openAct;
		QAction *runAct;
		QAction *haltAct;
		QAction *quitAct;
		QAction *aboutAct;

		QToolBar *toolbar;
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
