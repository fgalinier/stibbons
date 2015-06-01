/**
 * \file stibbons-highlighter.h
 * \brief The Highlighter header class
 * \author Florian Galiner
 * \version 1.0
 * \date 26/02/2015
 */
#pragma once

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <vector>

/**
 * \class StibbonsHighlighter
 * \brief The highlighter class that highlight code in Qt application.
 *
 * \author Florian Galiner
 */
class StibbonsHighlighter : public QSyntaxHighlighter {
 public:
	/**
	 * Constructor
	 * \param document the QTextDocument which contains the code
	 */
    StibbonsHighlighter(QTextDocument *document);
	
	/**
	 * Method called on each document's line that will highlight special language structure.
	 * \param line the line to highlight 
	 */
	virtual void highlightBlock(const QString &line);
 private:
	std::vector<std::pair<QRegExp,QTextCharFormat>> rules;
	
	QTextCharFormat keywordFormat;
	QTextCharFormat commentFormat;
	QTextCharFormat litFormat;
	QTextCharFormat worldInstrFormat;
	QTextCharFormat turtleInstrFormat;
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
