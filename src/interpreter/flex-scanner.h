#pragma once

#undef YY_DECL
#define YY_DECL int stibbons::FlexScanner::yylex()

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "y.tab.h"


namespace stibbons {
	class FlexScanner : public yyFlexLexer {
	public:
		FlexScanner(std::istream* in) : yyFlexLexer(in) {}
		int yylex(yy::parser::semantic_type* pyylval, yy::parser::location_type* loc) { 
			this->pyylval = pyylval; 
			this->loc = loc; 
			return yylex(); 
		}
		
	private:
		int yylex();
		yy::parser::semantic_type* pyylval;
		yy::parser::location_type* loc;
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
