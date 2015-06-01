/**
 * \file stibbons-highlighter.h
 * \brief The Highlighter header class
 * \author Florian Galiner
 * \version 1.0
 * \date 26/02/2015
 */
#pragma once

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QWidget>
#include <QPainter>
#include <QSize>

/**
 * \class StibbonsEditor
 * \brief The editor class in Qt application.
 *
 * \author Florian Galiner
 */
class StibbonsEditor : public QPlainTextEdit {
    Q_OBJECT

 public:
	/**
	 * Constructor
	 * \param parent the widget parent
	 */
    StibbonsEditor(QWidget *parent = 0);

	/**
	 * Repaint the lines number
	 * \param event the event that called the method
	 */
    void lineNumberAreaPaintEvent(QPaintEvent *event);

	/**
	 * Return the line number area width
	 * \return the line number area width
	 */
    int areaWidth() const;

 protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

	private slots:
		void updateLineNumberArea(const QRect &, int);
 
 private:
		QWidget *lineNumberArea;
};


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
