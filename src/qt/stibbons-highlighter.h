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
 * \file stibbons-highlighter.h
 * \brief The Highlighter header class
 * \author Florian Galiner
 * \version 1.1
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
