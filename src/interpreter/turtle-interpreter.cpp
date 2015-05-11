#include "turtle-interpreter.h"

#include <cstdio>
#include <cstring>

#include "../model/user-function.h"
#include "../model/type.h"
#include "semantic-exception.h"

namespace stibbons {
	ValuePtr TurtleInterpreter::interpret(InterpreterManager& manager,
										  AgentPtr agent,
										  const TreePtr tree,
										  TablePtr hashTable) {

		if(agent->getType() == Type::TURTLE){
			return this->interpret(manager,dynamic_pointer_cast<Turtle>(agent),tree,hashTable);
		}
		return nullptr;
	}


	ValuePtr TurtleInterpreter::interpret(InterpreterManager& manager,
										  TurtlePtr agent,
										  const TreePtr tree,
										  TablePtr hashTable) {
		
		if(tree != nullptr) {
		
			ValuePtr start = Interpreter::interpret(manager,agent,tree,hashTable);
			if(start != nullptr || std::get<0>(tree->getNode()) == 0 ) {
				return start;
			}
			else{
				switch(std::get<0>(tree->getNode())) {
					//Turtle cases:
				case yy::parser::token::FD: {
					auto val = this->interpret(manager,agent,tree->getSon(0),hashTable);
					if(val->getType() != Type::NUMBER) 
						throw SemanticException("FD",
												Type::NUMBER,
												val->getType(),
												getPosition(tree));
					agent->forward(dynamic_pointer_cast<Number>(val)->getValue());
				}
					break;
				case yy::parser::token::RT: {
					auto val = this->interpret(manager,agent,tree->getSon(0),hashTable);
					if(val->getType() != Type::NUMBER) 
						throw SemanticException("RT",
												Type::NUMBER,
												val->getType(),
												getPosition(tree));
					agent->turnRight(dynamic_pointer_cast<Number>(val)->getValue());
				}
					break;
				case yy::parser::token::LT: {
					auto val = this->interpret(manager,agent,tree->getSon(0),hashTable);
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
				case yy::parser::token::DIE:
					agent->die();
					break;
				case yy::parser::token::SEND:{
					auto msg = this->interpret(manager,agent,tree->getSon(0),hashTable);
					if(tree->getSons().size() > 1){
						auto dest = this->interpret(manager,agent,tree->getSon(1),hashTable);
						if(dest->getType() != Type::TABLE)
							throw SemanticException("In send at recipient",
													Type::TABLE,
													dest->getType(),
													getPosition(tree));

						for(int i=0;i<dynamic_pointer_cast<Table>(dest)->length();i++)
							agent->send(dynamic_pointer_cast<Turtle>(
									     dynamic_pointer_cast<Table>(dest)->getValue(i)),
									     msg);
					}
					else{
						agent->sendAll(msg);
					}
				}
					break;
				case yy::parser::token::RECV:{
						while (agent->checkMessage() <= 0)
							this_thread::sleep_for(chrono::milliseconds(10));
						auto msg = agent->recv();
						
						auto valMsg = msg.second;
						auto son1 = tree->getSon(0)->getNode();
						auto idMsg = dynamic_pointer_cast<String>(std::get<1>(son1))->getValue();
						
						agent->setProperty(idMsg,valMsg);

					if(tree->getSons().size() > 1){

						auto valExp = dynamic_pointer_cast<Turtle>(msg.first);
						auto son2 = tree->getSon(1)->getNode();
						auto idExp = dynamic_pointer_cast<String>(std::get<1>(son2))->getValue();

						agent->setProperty(idExp,valExp);
					}						
				}
					break;
				}
			}
		}
		
		return nullptr;
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
