#include "interpreter.h"

#include <cstdio>
#include <cstring>

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
  
	Value* Interpreter::interpret(const Tree* tree) {
		if(tree == nullptr) return nullptr;
		else {
			switch(std::get<0>(tree->getNode())) {
		   	//Sequence case:
			case 0:
				if(!tree->isLeaf()) {
					auto sons = tree->getSons();
					for(auto son : *sons) interpret(son);
				}
				break;
		  	//Basic cases:
			case yy::parser::token::FD: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("FD expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				turtle->forward(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) 
					throw SemanticException("RT expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				turtle->turnRight(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(tree->getSon(0));
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
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::BOOLEAN) 
					throw SemanticException("WHILE loop expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				while(dynamic_cast<Boolean*>(val)->getValue()) {
					this->interpret(tree->getSon(1));
					auto val = this->interpret(tree->getSon(0));
					if(val->getType() != Type::BOOLEAN)
					throw SemanticException("WHILE loop expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				}
			}
				break;
			case yy::parser::token::RPT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER)
					throw SemanticException("REPEAT loop expect a number",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				for(auto i=0;i<dynamic_cast<Number*>(val)->getValue();i++) {
					this->interpret(tree->getSon(1));
				}
			}
				break;
		   	//Conditionnal cases:
			case yy::parser::token::IF: {
				auto cond = this->interpret(tree->getSon(0));
				if(cond->getType() != Type::BOOLEAN) 
					throw SemanticException("IF expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				if(dynamic_cast<Boolean*>(cond)->getValue()){
					return this->interpret(tree->getSon(1));
				}
				else{
					return this->interpret(tree->getSon(2));
				}
			}
				break;
			//Variable cases:
			case yy::parser::token::ID: {
				return turtle->getProperty(dynamic_cast<String*>(std::get<1>(tree->getNode()))->getValue());
			}
				break;
			case '=': {
				auto val = this->interpret(tree->getSon(0));
				auto id = std::get<1>(tree->getNode());
				pair<string,Value*> prop = {dynamic_cast<String*>(id)->getValue(),val};
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
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("+ operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())+(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '-': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("- operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())-(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '*': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw SemanticException("* operator expect two numbers",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Number((dynamic_cast<Number*>(val1)->getValue())*(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '/': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
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
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
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
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("AND operator expect two booleans",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) && (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::OR: {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("OR operator expect two booleans",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) || (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::XOR: {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::BOOLEAN || val2->getType() != Type::BOOLEAN) 
					throw SemanticException("XOR operator expect two booleans",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean((dynamic_cast<Boolean*>(val1)->getValue()) ^ (dynamic_cast<Boolean*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::NOT: {
				auto val1 = this->interpret(tree->getSon(0));
				if(val1->getType() != Type::BOOLEAN) 
					throw SemanticException("NOT operator expect a boolean",
											yy::position(nullptr,std::get<0>(tree->getPosition()),
														 std::get<0>(tree->getPosition())));
				return new Boolean(!(dynamic_cast<Boolean*>(val1)->getValue()));
			}
				break;	
			}
		}

		//Operations tokens : EQ NEQ GT GEQ LS LEQ
		//Stibbons spécial tokens : DIE FCT_ID STRING COLOR NIL ID
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
