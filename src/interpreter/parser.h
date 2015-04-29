#pragma once

#include "flex-scanner.h"

namespace stibbons {
	class Parser {
	public:
	Parser(stibbons::TreePtr tree, stibbons::TablePtr worldDir, std::istream* in) 
		: scanner(new FlexScanner(in)), parser(*scanner,tree,worldDir) {}
		
		int parse() {
			return parser.parse();
		}
		
	private:
		FlexScanner* scanner;
		yy::parser parser;
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
