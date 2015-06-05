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
 * \file parser.h
 * \brief Parser class header.
 * \author Florian Galinier
 * \version 1.1
 * \date 26/04/15
 *
 * Definition of the Parser class.
 *
 */
#pragma once

#include "flex-scanner.h"

namespace stibbons {
	/**
	  * \class Parser
	  * \brief Class for syntaxic analysis.
	  *
	  * This class contain yy::parser, initialized with a FlexScanner. The parse() method is used
	  * to do syntax parsing.
	  *
	  * \author Florian Galinier
	  */
	class Parser {
	public:
	/**
	 * Parser constructor.
	 * \param[out] tree The abstract tree generated by our parser
	 * \param[out] worldDir a Table that contains world specifications 
	 * \param in The stream that will be parsed.
	 */
	Parser(stibbons::TreePtr tree, stibbons::TablePtr worldDir, std::istream* in) 
		: scanner(new FlexScanner(in)), parser(*scanner,tree,worldDir) {}
	/**
	 * Method used to generate abstract tree from input stream.
	 * \return 0 if no error occurred, 1 if parsing failed, 2 if parsing failed due to memory exhaustion (see Bison manual).
	 */	
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
