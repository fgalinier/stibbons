#include "stibbons-highlighter.h"

StibbonsHighlighter::StibbonsHighlighter(QTextDocument *document) : QSyntaxHighlighter(document) {}

void StibbonsHighlighter::highlightBlock(const QString &line) {
    enum { 
		InitialState = -1, 
		CommentState,
		SplQuoteState,
		DblQuoteState,
		TplQuoteState
	};

    int state = previousBlockState();
    int start = 0;

	QTextCharFormat keywordFormat;
	keywordFormat.setFontWeight(QFont::Bold);
	keywordFormat.setForeground(Qt::blue);
	QTextCharFormat commentFormat;
	commentFormat.setForeground(Qt::red);
	QTextCharFormat litFormat;
	litFormat.setForeground(Qt::darkGreen);
	QTextCharFormat worldInstrFormat;
	worldInstrFormat.setForeground(Qt::gray);
	QTextCharFormat turtleInstrFormat;
	turtleInstrFormat.setFontWeight(QFont::Bold);
	turtleInstrFormat.setForeground(Qt::magenta);

    for (int i = 0; i < line.length(); ++i) {
        switch (state) {
		case CommentState: 
			{
				if (line.mid(i, 2) == "*/") {
					setFormat(start, i - start + 2, commentFormat);
					start = i - start + 2;
					state = InitialState;
				}
			}
			break;
		case SplQuoteState:
			{
				if (line.mid(i,1) == "'" && line.mid(i-1,1) != "\\") {
					setFormat(start, i - start + 1, litFormat);
					start = i - start + 1;
					state = InitialState;
				}
			}
			break;
		case DblQuoteState:
			{
				if (line.mid(i,1) == "\"" && line.mid(i-1,1) != "\\") {
					setFormat(start, i - start + 1, litFormat);
					start = i - start + 1;
					state = InitialState;
				}
			}
			break;
		case TplQuoteState:
			{
				if (line.mid(i,3) == "\"\"\"") {
					setFormat(start, i - start + 3, litFormat);
					start = i - start + 3;
					state = InitialState;
				}
			}
			break;
		default: 
			{
				QRegExp worldInstr("^\\s*%[_a-z][\\-_a-z0-9]*.+");
				worldInstr.setCaseSensitivity(Qt::CaseInsensitive);
				QRegExp keyword("\\b(new|agent|function|for|repeat|while|if|else|and|or|xor|not)(?!-)\\b");
				keyword.setCaseSensitivity(Qt::CaseInsensitive);
				QRegExp lit("\\b(true|false|\\d+|null|null_t|number_t|boolean_t|string_t|color_t|table_t|type_t|turtle_t|zone_t|world_t)(?!-)\\b");
				lit.setCaseSensitivity(Qt::CaseInsensitive);
				QRegExp color("(#[a-f0-9]{3}|#[a-f0-9]{6})\\b");
				color.setCaseSensitivity(Qt::CaseInsensitive);
				QRegExp turtleInstr("\\b(fd|forward|lt|turn-left|rt|turn-right|pd|pen-down|pu|pen-up|send|recv|die)(?!-)\\b");
				turtleInstr.setCaseSensitivity(Qt::CaseInsensitive);
				
				if (line.mid(i, 2) == "/*") {
					start = i;
					state = CommentState;
				} else if (line.mid(i,3) == "\"\"\"") {
					start = i;
					state = TplQuoteState;
				} else if (line.mid(i,1) == "\"") {
					start = i;
					state = DblQuoteState;
				} else if (line.mid(i,1) == "'") {
					start = i;
					state = SplQuoteState;
				} else if (line.mid(i, 2) == "//") {
					setFormat(i, line.length() - i, commentFormat);
					return;
				}
				else {
					if ((start = line.indexOf(worldInstr,i)) > -1) {
						setFormat(start, worldInstr.matchedLength(), worldInstrFormat);
						i += worldInstr.matchedLength();
					}
					if ((start = line.indexOf(keyword,i)) > -1) {
						setFormat(start, keyword.matchedLength(), keywordFormat);
						i += keyword.matchedLength();
					}
					if ((start = line.indexOf(color,i)) > -1) {
						setFormat(start, color.matchedLength(), litFormat);
						i += color.matchedLength();
					}
					else if ((start = line.indexOf(lit,i)) > -1) {
						setFormat(start, lit.matchedLength(), litFormat);
						i += lit.matchedLength();
					}
					if ((start = line.indexOf(turtleInstr,i)) > -1) {
						setFormat(start, turtleInstr.matchedLength(), turtleInstrFormat);
						i += turtleInstr.matchedLength();
					}
				}
			}
			break;
		}
    }

	setCurrentBlockState(state);

    if (state == CommentState)
        setFormat(start, line.length() - start, commentFormat);
    if (state == TplQuoteState || state == DblQuoteState || state == SplQuoteState)
        setFormat(start, line.length() - start, litFormat);
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
