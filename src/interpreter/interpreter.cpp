#include "interpreter.h"

#include <cstdio>
#include <cstring>
#include <thread>

#include "../model/user-function.h"
#include "tree.h"
#include "y.tab.h"

extern FILE *yyin;

namespace stibbons {

	size_t Interpreter::waitTime = 0;

	yy::position Interpreter::getPosition(const TreePtr tree) {
		return yy::position(nullptr,
		                    std::get<0>(tree->getPosition()),
		                    std::get<0>(tree->getPosition()));
	}

	ValuePtr Interpreter::interpret(TurtlePtr turtle,
									const TreePtr tree,
									TablePtr hashTable) const throw(SemanticException) {
		this_thread::sleep_for(chrono::microseconds(waitTime));
		if(tree != nullptr) {
			switch(std::get<0>(tree->getNode())) {
		   	//Sequence case:
			case 0: {
				ValuePtr res = Nil::getInstance();
				if(!tree->isLeaf()) {
					auto sons = tree->getSons();
					for(auto son : sons) res = interpret(turtle,son,hashTable);
					return res;
				}
				break;
			}
		  	//Basic cases:
			case yy::parser::token::FD: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("FD",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				turtle->forward(dynamic_pointer_cast<Number>(val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("RT",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				turtle->turnRight(dynamic_pointer_cast<Number>(val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("LT",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				turtle->turnLeft(dynamic_pointer_cast<Number>(val)->getValue());
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
				ValuePtr res;
				if(val->getType() != Type::BOOLEAN) 
					throw SemanticException("WHILE",
					                        Type::BOOLEAN,
					                        val->getType(),
					                        getPosition(tree));
				while(dynamic_pointer_cast<Boolean>(val)->getValue()) {
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
				auto nb = dynamic_pointer_cast<Number>(val)->getValue();
				ValuePtr res;
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
				if(dynamic_pointer_cast<Boolean>(cond)->getValue()){
					return this->interpret(turtle,tree->getSon(1),hashTable);
				}
				else{
					return this->interpret(turtle,tree->getSon(2),hashTable);
				}
			}
				break;
			//Variable cases:
			case yy::parser::token::ID: {
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				if(hashTable) {
					auto got = hashTable->getValue(id);
					if (got->getType() != Type::NIL) {
						return hashTable->getValue(id);
					}
				}
				return turtle->getProperty(id);
			}
				break;
			case '=': {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				if (id == "color") {
					if(val->getType() != Type::COLOR) {
							throw SemanticException("color",
					                        Type::COLOR,
					                        val->getType(),
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
					}
					turtle->setColor(*dynamic_pointer_cast<Color>(val));
				}
				else {
					pair<string,ValuePtr> prop = {id,val};
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
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				auto zone = turtle->getZone();
				return zone->getProperty(id);
			}
				break;
			case yy::parser::token::ZONE: {
				auto val = this->interpret(turtle,tree->getSon(0),hashTable);
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				auto zone = turtle->getZone();
				if (id == "color") {
					if(val->getType() != Type::COLOR) {
							throw SemanticException("color",
					                        Type::COLOR,
					                        val->getType(),
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
					}
					zone->setColor(*dynamic_pointer_cast<Color>(val));
				}
				else {
					pair<string,ValuePtr> prop = {id,val};
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
			case '+':
				try {
					auto val1 = this->interpret(turtle,tree->getSon(0), hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1), hashTable);
					return val1->add(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '-':
				try {
					auto val1 = this->interpret(turtle,tree->getSon(0), hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1), hashTable);
					return val1->substract(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '*':
				try {
					auto val1 = this->interpret(turtle,tree->getSon(0), hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1), hashTable);
					return val1->multiply(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '/':
				try {
					auto val1 = this->interpret(turtle,tree->getSon(0), hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1), hashTable);
					return val1->divide(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '%':
				try {
					auto val1 = this->interpret(turtle,tree->getSon(0), hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1), hashTable);
					return val1->modulo(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
	   		//Boolean operation cases:
			case yy::parser::token::AND: {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("AND",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return make_shared<Boolean>((dynamic_pointer_cast<Boolean>(val1)->getValue()) && (dynamic_pointer_cast<Boolean>(val2)->getValue()));
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
				return make_shared<Boolean>((dynamic_pointer_cast<Boolean>(val1)->getValue()) || (dynamic_pointer_cast<Boolean>(val2)->getValue()));
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
				return make_shared<Boolean>((dynamic_pointer_cast<Boolean>(val1)->getValue()) ^ (dynamic_pointer_cast<Boolean>(val2)->getValue()));
			}
				break;
			case yy::parser::token::NOT: {
				auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
				if(val1->getType() != Type::BOOLEAN) 
					throw SemanticException("NOT",
					                        Type::BOOLEAN,
					                        val1->getType(),
					                        getPosition(tree));
				return make_shared<Boolean>(!(dynamic_pointer_cast<Boolean>(val1)->getValue()));
			}
				break;
			case yy::parser::token::EQ: {
				try{
					auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
					if(val1->getType() != val2->getType())
						throw SemanticException("==",
												val1->getType(),val1->getType(),
												val1->getType(),val2->getType(),
					                        getPosition(tree));

					return make_shared<Boolean>(val1->isEqual(val2));
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			}
				break; 
			case yy::parser::token::NEQ: {
				try{
					auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
					if(val1->getType() != val2->getType())
						throw SemanticException("!=",
												val1->getType(),val1->getType(),
												val1->getType(),val2->getType(),
					                        getPosition(tree));
					return make_shared<Boolean>(val1->isDifferent(val2));
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}			
			}
				break; 
			case yy::parser::token::GT: {
				try{
					auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
					if(val1->getType() != val2->getType())
						throw SemanticException(">",
												val1->getType(),val1->getType(),
												val1->getType(),val2->getType(),
					                        getPosition(tree));
					return make_shared<Boolean>(val1->isGreater(val2));
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			}
				break; 
			case yy::parser::token::GEQ: {
				try{
					auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
					if(val1->getType() != val2->getType())
						throw SemanticException(">=",
												val1->getType(),val1->getType(),
												val1->getType(),val2->getType(),
					                        getPosition(tree));
					return make_shared<Boolean>(val1->isGreaterOrEqual(val2));
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			}
				break;   
			case yy::parser::token::LS: {
				try{
					auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
					if(val1->getType() != val2->getType())
						throw SemanticException("<",
												val1->getType(),val1->getType(),
												val1->getType(),val2->getType(),
					                        getPosition(tree));
					return make_shared<Boolean>(val1->isLower(val2));
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			}
				break; 
			case yy::parser::token::LEQ: {
				try{
					auto val1 = this->interpret(turtle,tree->getSon(0),hashTable);
					auto val2 = this->interpret(turtle,tree->getSon(1),hashTable);
					if(val1->getType() != val2->getType())
						throw SemanticException("<=",
												val1->getType(),val1->getType(),
												val1->getType(),val2->getType(),
					                        getPosition(tree));
					return make_shared<Boolean>(val1->isLowerOrEqual(val2));
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			}
				break;
			// New agent
			case yy::parser::token::AGT: {
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				auto function = this->getFunctionFromTree(tree);
				turtle->getWorld()->createBreed(function,id);
			}
				break;
			case yy::parser::token::NEW: {
				auto type = std::get<1>(tree->getNode());
				std::string id;
				ValuePtr breed_v = Nil::getInstance();
				TreePtr paramTree;
				TurtlePtr newTurtle;
				
				if(type == nullptr) {
					id = "anonym agent";
					auto function = make_shared<UserFunction>(tree->getSon(0),vector<std::string>());
					BreedPtr breed = turtle->getWorld()->createBreed(function);
					paramTree = nullptr;
					auto fct = breed->getFunction();
					newTurtle = breed->createTurtle(turtle);
					auto inter = new Interpreter();
					auto params = getParams(fct,newTurtle,paramTree,hashTable,id);
					std::thread newThread(&Interpreter::interpretFunction,inter,fct,newTurtle,params);
					newThread.detach();
				}
				else {
					id = dynamic_pointer_cast<String>(type)->getValue();
					BreedPtr breed = turtle->getWorld()->getBreed(id);
					paramTree = tree;
					auto fct = breed->getFunction();
					newTurtle = breed->createTurtle(turtle);
					auto inter = new Interpreter();
					auto params = getParams(fct,newTurtle,paramTree,hashTable,id);
					std::thread newThread(&Interpreter::interpretFunction,inter,fct,newTurtle,params);
					newThread.detach();
				}
				return newTurtle;
			}
				break;
			// Functions
			case yy::parser::token::FCT: {
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				auto fct = this->getFunctionFromTree(tree);
				auto prop = std::pair<std::string,ValuePtr>(id,fct);
				turtle->setProperty(prop);
			}
				break;
			case yy::parser::token::CALL: {
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				auto fct = dynamic_pointer_cast<Function>(turtle->getProperty(id));
				if(fct == nullptr)
					throw SemanticException("Try to eval a non function value",
			                                getPosition(tree));
				if(fct->getType() != Type::FUNCTION)
					throw SemanticException("()",
					                        Type::FUNCTION,
					                        fct->getType(),
			                                getPosition(tree));
				auto params = getParams(fct,turtle,tree,hashTable,id);
				return this->interpretFunction(fct,turtle,params);
			}
				break;
			}
		}
 
		//Stibbons spécial tokens : DIE
		return Nil::getInstance();
	}

	ValuePtr Interpreter::interpret(AgentPtr agent,
	                              const TreePtr tree,
	                              TablePtr hashTable) const throw(SemanticException) {
		return interpret(dynamic_pointer_cast<Turtle>(agent), tree, hashTable);
	}

	FunctionPtr Interpreter::getFunctionFromTree(const TreePtr tree) const {
		auto fctTree = tree->getSon(0);
		auto params = std::vector<std::string>();
		auto sons = tree->getSons();
		for(size_t i=1;i<sons.size();i++) {
			params.push_back(
				dynamic_pointer_cast<String>(
					std::get<1>(
						sons.at(i)->getNode()
					)
				  )->getValue()
			);
		}
		return make_shared<UserFunction>(fctTree,params);
	}

	TablePtr Interpreter::getParams(FunctionPtr fct,
	                                TurtlePtr turtle,
	                                const TreePtr tree,
	                                TablePtr hashTable,
	                                std::string id) const {
//		auto newHashTable = (!hashTable)?make_shared<Table>():hashTable;
		auto newHashTable = make_shared<Table>();

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

		return newHashTable;
	}

	ValuePtr Interpreter::interpretFunction(FunctionPtr fct,
	                                        TurtlePtr turtle,
	                                        TablePtr params) const {
		return (*fct)(turtle, params);
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
