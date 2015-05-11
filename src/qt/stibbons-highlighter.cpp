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

    for (int i = 0; i < line.length(); ++i) {
        switch (state) {
		case CommentState: 
			{
				if (line.mid(i, 2) == "*/") {
					setFormat(start, i - start + 2, Qt::red);
					start = i - start + 2;
					state = InitialState;
				}
			}
			break;
		case SplQuoteState:
			{
				if (line.mid(i,1) == "'" && line.mid(i-1,1) != "\\") {
					setFormat(start, i - start + 1, Qt::darkMagenta);
					start = i - start + 1;
					state = InitialState;
				}
			}
			break;
		case DblQuoteState:
			{
				if (line.mid(i,1) == "\"" && line.mid(i-1,1) != "\\") {
					setFormat(start, i - start + 1, Qt::darkMagenta);
					start = i - start + 1;
					state = InitialState;
				}
			}
			break;
		case TplQuoteState:
			{
				if (line.mid(i,3) == "\"\"\"") {
					setFormat(start, i - start + 3, Qt::darkMagenta);
					start = i - start + 3;
					state = InitialState;
				}
			}
			break;
		default: 
			{
				QRegExp worldInstr("^[ ]*%[_a-z][\\-_a-z0-9]*.+");
				worldInstr.setCaseSensitivity(Qt::CaseInsensitive);
				QRegExp keyword("\\bnew|agent|function|for|repeat|while|if|else\\b");
				keyword.setCaseSensitivity(Qt::CaseInsensitive);
				
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
					setFormat(i, line.length() - i, Qt::red);
					return;
				}
				else if ((start = line.indexOf(worldInstr,i)) > -1) {
					setFormat(start, worldInstr.matchedLength(), Qt::gray);
					i += worldInstr.matchedLength();
				}
				else if ((start = line.indexOf(keyword,i)) > -1) {
					setFormat(start, keyword.matchedLength(), Qt::blue);
					i += keyword.matchedLength();
				}
			}
			break;
		}
    }

	setCurrentBlockState(state);

    if (state == CommentState)
        setFormat(start, line.length() - start, Qt::red);
    if (state == TplQuoteState || state == DblQuoteState || state == SplQuoteState)
        setFormat(start, line.length() - start, Qt::darkMagenta);
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
