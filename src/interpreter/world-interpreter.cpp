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

#include "world-interpreter.h"
#include "parser.h"

#include <cstring>
#include <sstream>

#include "../model/turtle.h"
#include "../model/user-function.h"

namespace stibbons {
	ValuePtr WorldInterpreter::interpret(InterpreterManager& manager,
									   AgentPtr agent,
									   const TreePtr tree,
									   TablePtr hashTable) {
		if(agent->getType() == Type::WORLD)
			return this->interpret(manager,dynamic_pointer_cast<World>(agent),tree,hashTable);

		throw SemanticException("Invalid action for the world",getPosition(tree));
	}

	ValuePtr WorldInterpreter::interpret(InterpreterManager& manager,
									   WorldPtr agent,
									   const TreePtr tree,
									   TablePtr hashTable) {
		if(tree != nullptr){
			ValuePtr start = Interpreter::interpret(manager,agent,tree,hashTable);

			if(start != nullptr || std::get<0>(tree->getNode()) == 0 )	
				return start;
			else{
				switch(std::get<0>(tree->getNode())) {
				case yy::parser::token::AGT: {
					//definition of new agent with corresponding breed
					auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
					auto function = this->getFunctionFromTree(manager,tree);
					agent->getWorld()->createBreed(function,id);
				}
					break;
				default:
					throw SemanticException("Invalid action for the world",getPosition(tree));		
					break;
				}
			}
		}

		return Nil::getInstance();
	}
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
