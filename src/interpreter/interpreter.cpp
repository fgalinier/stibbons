#include "interpreter.h"

#include <cstdio>
#include <cstring>
#include <thread>

#include "../model/user-function.h"
#include "turtle-interpreter.h"
#include "world-interpreter.h"
#include "y.tab.h"

namespace stibbons {

	size_t Interpreter::waitTime = 0;
	bool Interpreter::suspendFlag = false;
	condition_variable Interpreter::resumeCond;

	yy::position Interpreter::getPosition(const TreePtr tree) {
		return yy::position(nullptr,
		                    std::get<0>(tree->getPosition()),
		                    std::get<0>(tree->getPosition()));
	}	

	void Interpreter::checkHalt(){
		std::unique_lock<std::mutex> lock(suspendMutex);	
		while (suspendFlag != false){
			for(auto s : sons)
				resumeCond.wait(lock);
		}	

	}

	void Interpreter::start(AgentPtr agent,
							const TreePtr tree) {

		this->interpret(agent,tree,make_shared<Table>());

		while(!sons.empty()){
			sons[0]->join();
		}
	}

	ValuePtr Interpreter::interpret(AgentPtr agent,
									const TreePtr tree,
									TablePtr hashTable) throw(SemanticException) {
		checkHalt();
		this_thread::sleep_for(chrono::microseconds(waitTime));

		if(tree != nullptr) {
			switch(std::get<0>(tree->getNode())) {
				//Sequence case:
			case 0: {
				ValuePtr res = Nil::getInstance();
				if(!tree->isLeaf()) {
					auto sons = tree->getSons();
					for(auto son : sons) res = interpret(agent,son,hashTable);
					return res;
				}
				break;
			}
				//Loop cases:
			case yy::parser::token::WHL: {
				auto val = this->interpret(agent,tree->getSon(0),hashTable);
				ValuePtr res;
				if(val->getType() != Type::BOOLEAN) 
					throw SemanticException("WHILE",
					                        Type::BOOLEAN,
					                        val->getType(),
					                        getPosition(tree));
				while(dynamic_pointer_cast<Boolean>(val)->getValue()) {
					res = this->interpret(agent,tree->getSon(1),hashTable);
					val = this->interpret(agent,tree->getSon(0));
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
				auto val = this->interpret(agent,tree->getSon(0),hashTable);
				ValuePtr res;
				if(val->getType() != Type::NUMBER)
					throw SemanticException("REPEAT",
					                        Type::NUMBER,
					                        val->getType(),
					                        getPosition(tree));
				auto nb = dynamic_pointer_cast<Number>(val)->getValue();
				for(auto i=0;i<nb;i++) {
					res = this->interpret(agent,tree->getSon(1),hashTable);
				}
				return res;
			}
				break;
				//Conditionnal cases:
			case yy::parser::token::IF: {
				auto cond = this->interpret(agent,tree->getSon(0),hashTable);
				if(cond->getType() != Type::BOOLEAN) 
					throw SemanticException("IF",
					                        Type::BOOLEAN,
					                        cond->getType(),
					                        getPosition(tree));
				if(dynamic_pointer_cast<Boolean>(cond)->getValue()){
					return this->interpret(agent,tree->getSon(1),hashTable);
				}
				else{
					return this->interpret(agent,tree->getSon(2),hashTable);
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
				return agent->getProperty(id);
			}
				break;
			case yy::parser::token::TAB_ID: {
				auto tab = this->interpret(agent,tree->getSon(0),hashTable);
				if(tab->getType() != Type::TABLE) 
					throw SemanticException("[]",
					                        Type::TABLE,
					                        tab->getType(),
					                        getPosition(tree));
				auto key = this->interpret(agent,tree->getSon(1),hashTable);
				if(key->getType() == Type::STRING) {
					return dynamic_pointer_cast<Table>(tab)
						->getValue(dynamic_pointer_cast<String>(key)->getValue());
				}
				else if (key->getType() == Type::NUMBER) {
					return dynamic_pointer_cast<Table>(tab)
						->getValue(dynamic_pointer_cast<Number>(key)->getValue());
				}
				else {
					throw SemanticException("TABLE KEY",
											Type::STRING,
											Type::NUMBER,
											key->getType(),
											getPosition(tree));
				}
			}
				break;
			case '=': {
				return affectationOp(agent,tree,hashTable);
			}
				break;
			//Attribute cases:
			case yy::parser::token::ATT_ID: {
				auto t = this->interpret(agent,tree->getSon(0),hashTable);	
				AgentPtr target;
				if(t->getType() != Type::TURTLE 
					   && t->getType() != Type::WORLD 
					   && t->getType() != Type::ZONE)
						throw SemanticException(".",
												Type::AGENT,
												t->getType(),
												getPosition(tree));
						target = dynamic_pointer_cast<Agent>(t);
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				return target->getProperty(id);
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
			case yy::parser::token::TABLE:
				{
					auto val = make_shared<Table>();
					auto sons = tree->getSons();
					if(std::get<0>(sons.at(1)->getNode()) == yy::parser::token::PAIR) {
						for(auto s : sons) {
							auto key = this->interpret(agent,s->getSon(0),hashTable);
							auto value = this->interpret(agent,s->getSon(1),hashTable);
							if(key->getType() == Type::STRING) {
								val->setValue(
									dynamic_pointer_cast<String>(key)->getValue(),
									value
								);
							}
							else if (key->getType() == Type::NUMBER) {
								val->setValue(
									dynamic_pointer_cast<Number>(key)->getValue(),
									value
								);
							}
							else {
								throw SemanticException("TABLE KEY",
														Type::STRING,
														Type::NUMBER,
														key->getType(),
														getPosition(tree));
							}
						}
					}
					else {
						for(auto s : sons) {
							val->append(this->interpret(agent,s,hashTable));
						}
					}
					return val;
				}
				break;
				//Arithmetic cases:
			case '+':
				try {
					auto val1 = this->interpret(agent,tree->getSon(0), hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1), hashTable);
					return val1->add(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '-':
				try {
					auto val1 = this->interpret(agent,tree->getSon(0), hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1), hashTable);
					return val1->substract(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case yy::parser::token::UNARYMINUS: {
				auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
				if(val1->getType() != Type::NUMBER) 
					throw SemanticException("-",
					                        Type::NUMBER,
					                        val1->getType(),
					                        getPosition(tree));
				return dynamic_pointer_cast<Number>(val1)->unaryMinus();
			}
				break;
			case '*':
				try {
					auto val1 = this->interpret(agent,tree->getSon(0), hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1), hashTable);
					return val1->multiply(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '/':
				try {
					auto val1 = this->interpret(agent,tree->getSon(0), hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1), hashTable);
					return val1->divide(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
			case '%':
				try {
					auto val1 = this->interpret(agent,tree->getSon(0), hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1), hashTable);
					return val1->modulo(val2);
				}
				catch (std::domain_error e) {
					throw SemanticException(e.what(), getPosition(tree));
				}
				//Boolean operation cases:
			case yy::parser::token::AND: {
				auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
				auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("AND",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return make_shared<Boolean>((dynamic_pointer_cast<Boolean>(val1)->getValue()) && (dynamic_pointer_cast<Boolean>(val2)->getValue()));
			}
				break;
			case yy::parser::token::OR: {
				auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
				auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("OR",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return make_shared<Boolean>((dynamic_pointer_cast<Boolean>(val1)->getValue()) || (dynamic_pointer_cast<Boolean>(val2)->getValue()));
			}
				break;
			case yy::parser::token::XOR: {
				auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
				auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("XOR",
					                        Type::BOOLEAN, Type::BOOLEAN,
					                        val1->getType(), val2->getType(),
					                        getPosition(tree));
				return make_shared<Boolean>((dynamic_pointer_cast<Boolean>(val1)->getValue()) ^ (dynamic_pointer_cast<Boolean>(val2)->getValue()));
			}
				break;
			case yy::parser::token::NOT: {
				auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
				if(val1->getType() != Type::BOOLEAN) 
					throw SemanticException("NOT",
					                        Type::BOOLEAN,
					                        val1->getType(),
					                        getPosition(tree));
				return make_shared<Boolean>(!(dynamic_pointer_cast<Boolean>(val1)->getValue()));
			}
				break;
			case yy::parser::token::EQ: {
					auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1),hashTable);

					return make_shared<Boolean>(val1->isEqual(val2));
			}
				break; 
			case yy::parser::token::NEQ: {
					auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
					return make_shared<Boolean>(val1->isDifferent(val2));
			}
				break; 
			case yy::parser::token::GT: {
				try{
					auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
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
					auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
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
					auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
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
					auto val1 = this->interpret(agent,tree->getSon(0),hashTable);
					auto val2 = this->interpret(agent,tree->getSon(1),hashTable);
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
				agent->getWorld()->createBreed(function,id);
			}
				break;
			case yy::parser::token::NEW: {
				return newOp(agent,tree,hashTable);
			}
				break;
				// Functions
			case yy::parser::token::FCT: {
				auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
				auto fct = this->getFunctionFromTree(tree);
				agent->setProperty(id, fct);
			}
				break;
			case yy::parser::token::CALL: {	
				return callOp(agent,tree,hashTable);
			}
				break;
			default :
				return nullptr;
			}
		}
 
		//Stibbons spécial tokens : DIE
		return Nil::getInstance();
	}

	FunctionPtr Interpreter::getFunctionFromTree(const TreePtr tree) {
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
	                                AgentPtr agent,
	                                const TreePtr tree,
	                                TablePtr hashTable,
	                                std::string id) {
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
				auto val = Interpreter::interpret(agent,tree->getSon(i),hashTable);
				newHashTable->setValue(fct->getParams().at(i),val);
			}
		}

		return newHashTable;
	}

	ValuePtr Interpreter::interpretFunction(FunctionPtr fct,
	                                        AgentPtr agent,
	                                        TablePtr params) {
		return (*fct)(agent, params);
	}

	inline ValuePtr Interpreter::affectationOp(AgentPtr agent,TreePtr tree, TablePtr hashTable){
	auto val = this->interpret(agent,tree->getSon(1),hashTable);
				auto son = tree->getSon(0)->getNode();
				AgentPtr target;

				if (std::get<0>(son) == yy::parser::token::TAB_ID) {
					auto tab = this->interpret(agent,tree->getSon(0)->getSon(0),hashTable);
					if(tab->getType() != Type::TABLE) 
						throw SemanticException("[]",
												Type::TABLE,
												tab->getType(),
												getPosition(tree));
					if(tree->getSon(0)->getSons().size() > 1) {
						auto key = this->interpret(agent,tree->getSon(0)->getSon(1),hashTable);
						if(key->getType() == Type::STRING) {
							dynamic_pointer_cast<Table>(tab)
								->setValue(dynamic_pointer_cast<String>(key)->getValue(),val);
						}
						else if (key->getType() == Type::NUMBER) {
							dynamic_pointer_cast<Table>(tab)
								->setValue(dynamic_pointer_cast<Number>(key)->getValue(),val);
						}
						else {
							throw SemanticException("TABLE KEY",
													Type::STRING,
													Type::NUMBER,
													key->getType(),
													getPosition(tree));
						}
					}
					else
						dynamic_pointer_cast<Table>(tab)->append(val);
				}
				else {
				auto id = dynamic_pointer_cast<String>(std::get<1>(son))->getValue();
					if (std::get<0>(son) == yy::parser::token::ATT_ID) {
						auto t = this->interpret(agent,tree->getSon(0)->getSon(0),hashTable);
						if(t->getType() != Type::TURTLE 
						   && t->getType() != Type::WORLD 
						   && t->getType() != Type::ZONE)
							throw SemanticException(".",
													Type::TURTLE,
													t->getType(),
													getPosition(tree));
						target = dynamic_pointer_cast<Agent>(t);
					}
					else
						target = agent;
				
					if(hashTable) {
						auto got = hashTable->getValue(id);
						if (got->getType() != Type::NIL) {
							hashTable->setValue(id,val);
						}
					}
					target->setProperty(id,val);
				}				

				return val;
	}

	inline TurtlePtr Interpreter::newOp(AgentPtr agent,TreePtr tree, TablePtr hashTable){
		auto type = std::get<1>(tree->getNode());
		std::string id;
		TurtlePtr newTurtle;
		TreePtr paramTree;
		BreedPtr breed;

		if(type == nullptr) {
			id = "anonym agent";
			auto function = make_shared<UserFunction>(tree->getSon(0),vector<std::string>());
			breed = agent->getWorld()->createBreed(function);
			paramTree = nullptr;

		}
		else {
			id = dynamic_pointer_cast<String>(type)->getValue();
			breed = agent->getWorld()->getBreed(id);
			paramTree = tree;
		}

		auto fct = breed->getFunction();
		if(agent->getType() == Type::TURTLE)
			newTurtle = breed->createTurtle(dynamic_pointer_cast<Turtle>(agent));
		else
			newTurtle = breed->createTurtle(agent);					
		auto params = getParams(fct,agent,paramTree,hashTable,id);
		auto inter = make_shared<TurtleInterpreter>();

		auto newThread = new thread (&Interpreter::interpretFunction,
									 inter,
									 fct,
									 newTurtle,
									 params);
		sons.push_back(newThread);
			
		return newTurtle;
	}

	inline ValuePtr Interpreter::callOp(AgentPtr agent,TreePtr tree, TablePtr hashTable){
		auto id = dynamic_pointer_cast<String>(std::get<1>(tree->getNode()))->getValue();
		auto fct = dynamic_pointer_cast<Function>(agent->getProperty(id));
		if(fct == nullptr)
			throw SemanticException("Try to eval a non function value",
									getPosition(tree));
		if(fct->getType() != Type::FUNCTION)
			throw SemanticException("()",
									Type::FUNCTION,
									fct->getType(),
									getPosition(tree));
		auto params = getParams(fct,agent,tree,hashTable,id);
		try {
			return this->interpretFunction(fct,agent,params);
		}
		catch (std::domain_error e) {
			throw SemanticException(e.what(), getPosition(tree));
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
