#include "turtle-interpreter.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "../model/user-function.h"
#include "../model/type.h"
#include "semantic-exception.h"

namespace stibbons {
	TurtleInterpreter::TurtleInterpreter(){
		std::cout<<"turtle construct"<<std::endl;
	sleep(5);
}

	/*
	TurtleInterpreter::TurtleInterpreter(TurtlePtr agent,
										 const TreePtr tree,
										 TablePtr hashTable) {
		std::cout<<"construct : turtleinterpreter"<<std::endl;
		sleep(5);

		this->interpret(agent,tree,hashTable);
		}*/

	ValuePtr TurtleInterpreter::interpret(AgentPtr agent,
										  const TreePtr tree,
										  TablePtr hashTable) throw(SemanticException) {

		std::cout<<"turtleinterpreter(agent)"<<std::endl;
		sleep(5);
		if(agent->getType() == Type::TURTLE){
		std::cout<<"turtleinterpreter(turtle)"<<std::endl;
		sleep(5);
			return this->interpret(dynamic_pointer_cast<Turtle>(agent),tree,hashTable);
		}
		return nullptr;
	}


	ValuePtr TurtleInterpreter::interpret(TurtlePtr agent,
										  const TreePtr tree,
										  TablePtr hashTable) throw(SemanticException) {
		
		std::cout<<"turtleinterpreter"<<std::endl;
		sleep(5);
		ValuePtr start = Interpreter::interpret(agent,tree,hashTable);
		
		if(start != nullptr) {
			return start;
		}
		else{
			switch(std::get<0>(tree->getNode())) {
				//Turtle cases:
			case yy::parser::token::FD: {
				auto val = this->interpret(agent,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("FD",
											Type::NUMBER,
											val->getType(),
											getPosition(tree));
				std::cout<<"fd !!!"<<std::endl;
				agent->forward(dynamic_pointer_cast<Number>(val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(agent,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("RT",
											Type::NUMBER,
											val->getType(),
											getPosition(tree));
				agent->turnRight(dynamic_pointer_cast<Number>(val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(agent,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("LT",
											Type::NUMBER,
											val->getType(),
											getPosition(tree));
				agent->turnLeft(dynamic_pointer_cast<Number>(val)->getValue());
			}
				break;
			case yy::parser::token::PU:
				agent->penUp();
				break;
			case yy::parser::token::PD:
				agent->penDown();
				break;
			default :
				throw SemanticException("invalid action for a turtle",
										getPosition(tree));	
			}
		}
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
