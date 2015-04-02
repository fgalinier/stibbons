#include "interpreter.h"

#include <cstdio>
#include <cstring>
#include <thread>

#include "tree.h"
#include "semantic-exception.h"
#include "y.tab.h"

extern FILE *yyin;

namespace stibbons {

	Interpreter::Interpreter(Turtle* turtle): turtle(turtle) {}

	Tree* Interpreter::parse(const char *program) const {
		size_t size = strlen(program);

		// Copy the string to make it non-constant
		void *buffer = malloc(size);
		memcpy(buffer, program, size);

		// Create a new file stream for the program string
		FILE *file = fmemopen(buffer, size, "r+");
		yyin = file;

		// Parse the program
		Tree *tree = new Tree(0,nullptr);
		yy::parser* pparser = new yy::parser(tree);
		pparser->parse();

		// Destroy the file stream and the buffer
		fclose(file);
		free(buffer);

		return tree;
	}
  
	Value* Interpreter::interpret(const Tree* tree,unordered_map<std::string,Value*>* hashTable) {
		if(tree != nullptr) {
			switch(std::get<0>(tree->getNode())) {
		   	//Sequence case:
			case 0:
				Value* res;
				if(!tree->isLeaf()) {
					auto sons = tree->getSons();
					for(auto son : *sons) res = interpret(son,hashTable);
					return res;
				}
				break;
		  	//Basic cases:
			case yy::parser::token::FD: {
				auto val = this->interpret(tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("FD expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				turtle->forward(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("RT expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				turtle->turnRight(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("LT expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
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
				auto val = this->interpret(tree->getSon(0),hashTable);
				Value* res;
				if(val->getType() != Type::BOOLEAN) 
					throw SemanticException("WHILE loop expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				while(dynamic_cast<Boolean*>(val)->getValue()) {
					res = this->interpret(tree->getSon(1),hashTable);
					auto val = this->interpret(tree->getSon(0));
					if(val->getType() != Type::BOOLEAN)
					throw SemanticException("WHILE loop expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				}
				return res;
			}
				break;
			case yy::parser::token::RPT: {
				auto val = this->interpret(tree->getSon(0));
				auto nb = dynamic_cast<Number*>(val)->getValue();
				Value* res;
				if(val->getType() != Type::NUMBER)
					throw SemanticException("REPEAT loop expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				for(auto i=0;i<nb;i++) {
					res = this->interpret(tree->getSon(1),hashTable);
				}
				return res;
			}
				break;
		   	//Conditionnal cases:
			case yy::parser::token::IF: {
				auto cond = this->interpret(tree->getSon(0),hashTable);
				if(cond->getType() != Type::BOOLEAN) 
					throw SemanticException("IF expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				if(dynamic_cast<Boolean*>(cond)->getValue()){
					return this->interpret(tree->getSon(1),hashTable);
				}
				else{
					return this->interpret(tree->getSon(2),hashTable);
				}
			}
				break;
			//Variable cases:
			case yy::parser::token::ID: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				if(hashTable) {
					auto got = hashTable->find(id);
					if (got != hashTable->end())
						return hashTable->at(id);
				}
				return turtle->getProperty(id);
			}
				break;
			case '=': {
				auto val = this->interpret(tree->getSon(0),hashTable);
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				pair<string,Value*> prop = {id,val};
				if(hashTable) {
					auto got = hashTable->find(id);
					if (got != hashTable->end()) {
						(*hashTable)[id] = val;
					}
				}
				turtle->setProperty(prop);
				return val;
			}
				break;
		   	//Type cases:
			case yy::parser::token::NUMBER:		
				return std::get<1>(tree->getNode());
				break;
			case yy::parser::token::BOOLEAN:
				return std::get<1>(tree->getNode());
				break;
		   	//Arithmetic cases:
			case '+': {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("+ operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())+(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '-': {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("- operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())-(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '*': {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("* operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())*(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '/': {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("/ operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				if(dynamic_cast<Number*>(val2)->getValue() == 0) 
					throw SemanticException("Cannot divide by 0",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())/(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '%': {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("% operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				if(dynamic_cast<Number*>(val2)->getValue() == 0) 
					throw SemanticException("Cannot divide by 0",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number(((int) dynamic_cast<Number*>(val1)->getValue())%((int) dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
	   		//Boolean operation cases:
			case yy::parser::token::AND: {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("AND operator expect two booleans",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) && (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::OR: {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("OR operator expect two booleans",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) || (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::XOR: {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				auto val2 = this->interpret(tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("XOR operator expect two booleans",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) ^ (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::NOT: {
				auto val1 = this->interpret(tree->getSon(0),hashTable);
				if(val1->getType() != Type::BOOLEAN) 
					throw SemanticException("NOT operator expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean(!(dynamic_cast<Boolean*>(val1)->getValue()));
			}
				break;  
			// New agent
			case yy::parser::token::NEW: {
				auto type = std::get<1>(tree->getNode());
				if(type == nullptr) {

					auto function = new Function();
					//auto function = new Function(*(tree->getSon(0)),vector<std::string>()));
					auto breed = turtle->getWorld()->createBreed(*function);
					auto newTurtle = breed->createTurtle();
					auto inter = new Interpreter(newTurtle);
					std::thread newThread(&Interpreter::interpret, 
										  inter, 
										  tree->getSon(0),
										  hashTable);
					newThread.detach();
				}
			}
				break;
			// Functions
			case yy::parser::token::FCT: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto fctTree = tree->getSon(0);
				auto params = new std::vector<std::string>();
				auto sons = tree->getSons();
				for(size_t i=1;i<sons->size();i++) {
					params->push_back(
						dynamic_cast<String*>(
							std::get<1>(
								sons->at(i)->getNode()
							)
						)->getValue()
					);
				}
				auto fct = new Function(fctTree,*params);
				auto prop = std::pair<std::string,Value*>(id,fct);
				turtle->setProperty(prop);
			}
				break;
			case yy::parser::token::CALL: {
				auto id = dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue();
				auto fct = dynamic_cast<Function*>(turtle->getProperty(id));
				if(fct->getType() != Type::FUNCTION)
					throw SemanticException("Try to eval a non function value",
										yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				if(fct->getArg().size() != tree->getSons()->size()) {
					std::ostringstream oss; 
					oss<<"No matching function for "<<id<<" with "<<tree->getSons()->size()<<" parameters";
					throw SemanticException(oss.str().c_str(),
										yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				}	
				auto newHashTable = (!hashTable)?(new unordered_map<std::string,Value*>()):hashTable;
				
				for(size_t i=0;i<fct->getArg().size();i++) {
					(*newHashTable)[fct->getArg().at(i)] = this->interpret(tree->getSon(i),hashTable);
				}
				auto fctTree = dynamic_cast<Function*>(fct)->getValue();
				return this->interpret(fctTree,newHashTable);
			}
				break;
			}
		}
 
		//Operations tokens : EQ NEQ GT GEQ LS LEQ
		//Stibbons spécial tokens : DIE FCT_ID STRING COLOR NIL ID
		return &Nil::getInstance();
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
