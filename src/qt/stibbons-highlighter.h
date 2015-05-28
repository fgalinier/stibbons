#pragma once

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <vector>

class StibbonsHighlighter : public QSyntaxHighlighter {
 public:
    StibbonsHighlighter(QTextDocument *document);
	virtual void highlightBlock(const QString &text);
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
