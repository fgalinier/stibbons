#include "interpreter.h"

#include <cstdio>
#include <cstring>
#include <thread>

#include "../model/user-function.h"
#include "tree.h"
#include "semantic-exception.h"
#include "y.tab.h"

extern FILE *yyin;

namespace stibbons {

	yy::position Interpreter::getPosition(const TreePtr tree) {
		return yy::position(nullptr,
		                    std::get<0>(tree->getPosition()),
		                    std::get<0>(tree->getPosition()));
	}

	Value* Interpreter::interpret(Turtle* turtle,
	                              const TreePtr tree,
								  Table* hashTable) const {
		if(tree != nullptr) {
			switch(std::get<0>(tree->getNode())) {
		   	//Sequence case:
			case 0:
				Value* res;
				if(!tree->isLeaf()) {
					auto sons = tree->getSons();
					for(auto son : sons) res = interpret(turtle,son,hashTable);
					return res;
				}
				break;
		  	//Basic cases:
			case yy::parser::token::FD: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("FD",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				turtle->forward(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("RT",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				turtle->turnRight(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("LT",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				turtle->turnLeft(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::PU:
				turtle->penUp();
				break;
			case yy::parser::token::PD:
				turtle->penDown();
				break;
		   	//Loop cases:
			case yy::parser::token::WHL: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				Value* res;
				if(val->getType() != Type::BOOLEAN) 
					throw SemanticException("WHILE",
					                        Type::BOOLEAN,
					                        val->getType(),
					                        getPosition(tree));
				while(dynamic_cast<Boolean*>(val)->getValue()) {
					res = this->interpret(turtle,tree->getSon(1),hashTable);
					auto val = this->interpret(turtle,tree->getSon(0));
					if(val->getType() != Type::BOOLEAN)
					throw SemanticException("WHILE",
					                        Type::BOOLEAN,
					                        val->getType(),
					                        getPosition(tree));
				}
				return res;
			}
				break;
			case yy::parser::token::RPT: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				auto nb = dynamic_cast<Number*>(val)->getValue();
				Value* res;
				if(val->getType() != Type::NUMBER)
					throw SemanticException("REPEAT",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				for(auto i=0;i<nb;i++) {
					res = this->interpret(turtle,tree->getSon(1),hashTable);
				}
				return res;
			}
				break;
		   	//Conditionnal cases:
			case yy::parser::token::IF: {
				auto cond = this->interpret(turtle,tree->getSon(0),hashTable);
				if(cond->getType() != Type::BOOLEAN) 
					throw SemanticException("IF",
					                        Type::BOOLEAN,
					                        cond->getType(),
					                        getPosition(tree));
				if(dynamic_cast<Boolean*>(cond)->getValue()){
					return this->interpret(turtle,tree->getSon(1),hashTable);
				}
				else{
					return this->interpret(turtle,tree->getSon(2),hashTable);
				}
			}
				break;
			//Variable cases:
			case yy::parser::token::ID: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				if(hashTable) {
					auto got = hashTable->getValue(id);
					if (got != &Nil::getInstance())
						return hashTable->getValue(id);
				}
				return turtle->getProperty(id);
			}
				break;
			case '=': {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				if (id == "color") {
					if(val->getType() != Type::COLOR) {
							throw SemanticException("color",
					                        Type::COLOR,
					                        val->getType(),
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
					}
					turtle->setColor(*(dynamic_cast<Color*>(val)));
				}
				else {
					pair<string,Value*> prop = {id,val};
					if(hashTable) {
						auto got = hashTable->getValue(id);
						if (got->getType() != Type::NIL) {
							hashTable->setValue(id,val);
						}
					}
					turtle->setProperty(prop);
				}
				return val;
			}
				break;
			//Zone cases:
			case yy::parser::token::ZID: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto zone = turtle->getZone();
				return zone->getProperty(id);
			}
				break;
			case yy::parser::token::ZONE: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto zone = turtle->getZone();
				if (id == "color") {
					if(val->getType() != Type::COLOR) {
							throw SemanticException("color",
					                        Type::COLOR,
					                        val->getType(),
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
					}
					zone->setColor(*(dynamic_cast<Color*>(val)));
				}
				else {
					pair<string,Value*> prop = {id,val};
					zone->setProperty(prop);
				}
				return val;
			}
				break;
		   	//Type cases:
			case yy::parser::token::NUMBER:
			case yy::parser::token::STRING:
			case yy::parser::token::COLOR:
			case yy::parser::token::BOOLEAN:
			case yy::parser::token::NIL:
				return std::get<1>(tree->getNode());
				break;
		   	//Arithmetic cases:
			case '+': {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("+",
					                        Type::NUMBER, Type::NUMBER,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return new Number((dynamic_cast<Number*>(val1)->getValue())+(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '-': {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("-",
					                        Type::NUMBER, Type::NUMBER,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return new Number((dynamic_cast<Number*>(val1)->getValue())-(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '*': {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("*",
					                        Type::NUMBER, Type::NUMBER,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return new Number((dynamic_cast<Number*>(val1)->getValue())*(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '/': {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("/",
					                        Type::NUMBER, Type::NUMBER,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				if(dynamic_cast<Number*>(val2)->getValue() == 0) 
					throw SemanticException("/: Cannot divide by 0",
					                        getPosition(tree));
				return new Number((dynamic_cast<Number*>(val1)->getValue())/(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '%': {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("%",
					                        Type::NUMBER, Type::NUMBER,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				if(dynamic_cast<Number*>(val2)->getValue() == 0) 
					throw SemanticException("%: Cannot divide by 0",
					                        getPosition(tree));
				return new Number(((int) dynamic_cast<Number*>(val1)->getValue())%((int) dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
	   		//Boolean operation cases:
			case yy::parser::token::AND: {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("AND",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) && (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::OR: {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("OR",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) || (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::XOR: {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("XOR",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) ^ (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::NOT: {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val1->getType() != Type::BOOLEAN) 
					throw SemanticException("NOT",
					                        Type::BOOLEAN,
					                        val1->getType(),
					                        getPosition(tree));
				return new Boolean(!(dynamic_cast<Boolean*>(val1)->getValue()));
			}
				break;  
			// New agent
			case yy::parser::token::AGT: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto function = this->getFunctionFromTree(tree);
				turtle->getWorld()->createBreed(*function,id);
			}
				break;
			case yy::parser::token::NEW: {
				auto type = std::get<1>(tree->getNode());
				std::string id;
				Breed* breed;
				TreePtr paramTree;
				if(type == nullptr) {
					id = "anonym agent";
					auto function = new UserFunction(tree->getSon(0),vector<std::string>());
					breed = turtle->getWorld()->createBreed(*function);
				}
				else {
					id = dynamic_cast<String*>(type)->getValue();
					breed = turtle->getWorld()->getBreed(id);
					paramTree = tree;
				}
				auto fct = breed->getFunction();
				auto newTurtle = breed->createTurtle(turtle);
				auto inter = new Interpreter();
				std::thread newThread(&Interpreter::interpretFunction,inter,fct,newTurtle,paramTree,hashTable,id);
				newThread.detach();
			}
				break;
			// Functions
			case yy::parser::token::FCT: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto fct = this->getFunctionFromTree(tree);
				auto prop = std::pair<std::string,Value*>(id,fct);
				turtle->setProperty(prop);
			}
				break;
			case yy::parser::token::CALL: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto fct = dynamic_cast<Function*>(turtle->getProperty(id));
				if(fct == nullptr)
					throw SemanticException("Try to eval a non function value",
			                                getPosition(tree));
				if(fct->getType() != Type::FUNCTION)
					throw SemanticException("()",
					                        Type::FUNCTION,
					                        fct->getType(),
			                                getPosition(tree));
				return this->interpretFunction(fct,turtle,tree,hashTable,id);
			}
				break;
			}
		}
 
		//Operations tokens : EQ NEQ GT GEQ LS LEQ
		//Stibbons spécial tokens : DIE STRING NIL
		return &Nil::getInstance();
	}

	Value* Interpreter::interpret(Agent* agent,
	                              const TreePtr tree,
	                              Table* hashTable) const {
		return interpret(dynamic_cast<Turtle*>(agent), tree, hashTable);
	}

	Function* Interpreter::getFunctionFromTree(const TreePtr tree) const {
		auto fctTree = tree->getSon(0);
		auto params = new std::vector<std::string>();
		auto sons = tree->getSons();
		for(size_t i=1;i<sons.size();i++) {
			params->push_back(
				dynamic_cast<String*>(
					std::get<1>(
						sons.at(i)->getNode()
					)
				  )->getValue()
			);
		}
		return new UserFunction(fctTree,*params);
	}

	Value* Interpreter::interpretFunction(Function* fct,
	                                      Turtle* turtle,
										  const TreePtr tree,
										  Table* hashTable,
										  std::string id) const {
		auto newHashTable = (!hashTable)?new Table():hashTable;

		if(tree) {
			if(fct->getParams().size() != tree->getSons().size()) {
				std::ostringstream oss;
				oss<<"No matching function for "
				   <<id
				   <<" with "
				   <<tree->getSons().size()
				   <<" parameters";
				throw SemanticException(oss.str().c_str(),
										getPosition(tree));
			}

			for(size_t i=0;i<fct->getParams().size();i++) {
				auto val = this->interpret(turtle,tree->getSon(i),hashTable);
				newHashTable->setValue(fct->getParams().at(i),val);
			}
		}

		return (*fct)(turtle, newHashTable);
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
