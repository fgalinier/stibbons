#include "stibbons-highlighter.h"

StibbonsHighlighter::StibbonsHighlighter(QTextDocument *document) : QSyntaxHighlighter(document) {
	keywordFormat.setFontWeight(QFont::Bold);
	keywordFormat.setForeground(Qt::blue);
	commentFormat.setForeground(Qt::red);
	commentFormat.setFontItalic(true);
	litFormat.setForeground(Qt::darkGreen);
	worldInstrFormat.setForeground(Qt::gray);
	worldInstrFormat.setFontWeight(QFont::Bold);
	turtleInstrFormat.setFontWeight(QFont::Bold);
	turtleInstrFormat.setForeground(Qt::magenta);
	
	QStringList keywords;
	QStringList turtleInstrs;
	QStringList lits;
	QStringList worldInstr("^\\s*(%[_a-z][\\-_a-z0-9]*)(\\s.+)?");

	keywords << "\\bnew\\b" << "\\bagent\\b" << "\\bfunction\\b" << "\\bfor\\b" << "\\brepeat\\b" 
			 << "\\bwhile\\b" << "\\bif\\b" << "\\belse\\b" << "\\band\\b" << "\\bor\\b"
			 << "\\bxor\\b" << "\\bnot\\b";

	turtleInstrs <<  "\\bfd\\b" << "\\bforward\\b" << "\\blt\\b" << "\\bturn_left\\b" << "\\brt\\b"
				 << "\\bturn_right\\b" << "\\bpd\\b" << "\\bpen_down\\b" << "\\bpu\\b" 
				 << "\\bpen_up\\b" << "\\bsend\\b" << "\\brecv\\b" << "\\bdie\\b";

	lits << "\\btrue\\b" << "\\bfalse\\b" << "\\b\\d+\\b" << "\\bnull\\b" << "\\bnull_t\\b"
		 << "\\bnumber_t\\b" << "\\bboolean_t\\b" << "\\bstring_t\\b" << "\\bcolor_t\\b"
		 << "\\btable_t\\b" << "\\btype_t\\b" << "\\bturtle_t\\b" << "\\bzone_t\\b" 
		 << "\\bworld_t\\b" << "#([a-f0-9]){3}\\b" << "#([a-f0-9]){6}\\b" << "\\bnone\\b" 
		 << "\\bbounce\\b" << "\\bwrap\\b";
	
	rules.push_back({QRegExp("^\\s*(%[_a-z][\\-_a-z0-9]*)\\b"),worldInstrFormat});

	for (auto pattern : keywords) {
		rules.push_back({QRegExp(pattern),keywordFormat});
	}
	for (auto pattern : turtleInstrs) {
		rules.push_back({QRegExp(pattern),turtleInstrFormat});
	}
	for (auto pattern : lits) {
		rules.push_back({QRegExp(pattern),litFormat});
	}
}

void StibbonsHighlighter::highlightBlock(const QString &line) {
    enum { 
		InitialState = -1, 
		CommentState,
		SplQuoteState,
		DblQuoteState,
		TplQuoteState
	};

	for(auto rule : rules) {
		rule.first.setCaseSensitivity(Qt::CaseInsensitive);
		auto index = rule.first.indexIn(line);
		while (index > -1) {
			int l = rule.first.matchedLength();
			setFormat(index, l, rule.second);
			index = rule.first.indexIn(line, index + l);
		}
	}

	int commentStart = 0;
	int splStart = 0;
	int dblStart = 0;
	int tplStart = 0;
    int state = previousBlockState();

    for (int i = 0; i < line.length(); ++i) {
        switch (state) {
		case CommentState:
			if (line.mid(i, 2) == "*/") {
				setFormat(commentStart, i - commentStart + 2, commentFormat);
				state = InitialState;
			}
			break;
		case SplQuoteState:
			if (line.mid(i, 1) == "'") {
				setFormat(splStart, i - splStart + 1, litFormat);
				state = InitialState;
			}
			break;
		case DblQuoteState:
			if (line.mid(i, 1) == "\"") {
				setFormat(dblStart, i - dblStart + 1, litFormat);
				state = InitialState;
			}
			break;
		case TplQuoteState:
			if (line.mid(i, 3) == "\"\"\"") {
				setFormat(tplStart, i - tplStart + 3, litFormat);
				state = InitialState;
			}
			break;
		default:
			if (line.mid(i, 2) == "//") {
				setFormat(i+1, line.length() - i + 1, commentFormat);
				return;
			}
			if (line.mid(i, 2) == "/*") {
				commentStart = i+1;
				state = CommentState;
				break;
			}
			if (line.mid(i, 1) == "'") {
				splStart = i;
				state = SplQuoteState;
				break;
			}
			if (line.mid(i, 1) == "\"") {
				dblStart = i;
				state = DblQuoteState;
				break;
			}
			if (line.mid(i, 3) == "\"\"\"") {
				tplStart = i+2;
				state = TplQuoteState;
				break;
			}
			break;
		}
	}

	if (state == CommentState)
        setFormat(commentStart, line.length() - commentStart, commentFormat);
    if (state == SplQuoteState)
        setFormat(splStart, line.length() - splStart, litFormat);
    if (state == DblQuoteState)
        setFormat(dblStart, line.length() - dblStart, litFormat);
    if (state == TplQuoteState)
        setFormat(tplStart, line.length() - tplStart, litFormat);

	setCurrentBlockState(state);
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
