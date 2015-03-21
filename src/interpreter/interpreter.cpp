#include "interpreter.h"

#include <stdexcept>
#include <cstdio>
#include <cstring>

#include "tree.h"
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
			case 0:
				if(!tree->isLeaf()) {
					auto sons = tree->getSons();
					for(auto son : *sons) interpret(son);
				}
				break;
			case yy::parser::token::WHL: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::BOOLEAN) throw std::exception();
				while(dynamic_cast<Boolean*>(val)->getValue()) {
					this->interpret(tree->getSon(1));
					auto val = this->interpret(tree->getSon(0));
					if(val->getType() != Type::BOOLEAN) throw std::exception();
				}
			}
				break;
			case yy::parser::token::RPT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				for(auto i=0;i<dynamic_cast<Number*>(val)->getValue();i++) {
					this->interpret(tree->getSon(1));
				}
			}
				break;
			case yy::parser::token::FD: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				turtle->forward(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				turtle->turnRight(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				turtle->turnLeft(dynamic_cast<Number*>(val)->getValue());
			}
				break;
			case yy::parser::token::PU:
				turtle->penUp();
				break;
			case yy::parser::token::PD:
				turtle->penDown();
				break;
			case yy::parser::token::NUMBER:
				return std::get<1>(tree->getNode());
				break;
			case yy::parser::token::BOOLEAN:
				return std::get<1>(tree->getNode());
				break;
			case '+': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				return new Number((dynamic_cast<Number*>(val1)->getValue())+(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '-': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				return new Number((dynamic_cast<Number*>(val1)->getValue())-(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '*': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				return new Number((dynamic_cast<Number*>(val1)->getValue())*(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '/': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				if(dynamic_cast<Number*>(val2)->getValue() == 0) 
					throw std::exception();
				return new Number((dynamic_cast<Number*>(val1)->getValue())/(dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case '%': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				if(dynamic_cast<Number*>(val2)->getValue() == 0) 
					throw std::exception();
				return new Number(((int) dynamic_cast<Number*>(val1)->getValue())%((int) dynamic_cast<Number*>(val2)->getValue()));
			}
				break;
			case yy::parser::token::IF: {
				auto cond = this->interpret(tree->getSon(0));
				if(cond->getType() != Type::BOOLEAN) 
					throw std::exception();
				if(cond){
					return this->interpret(tree->getSon(1));
				}
				else{
					return this->interpret(tree->getSon(2));
				}
			}
			case yy::parser::token::ELSE: {
				auto val1 = this->interpret(tree->getSon(0));
				return val1;
			}
				break;
			}
		}

		//DIE AND OR XOR NOT EQ NEQ GT GEQ LS LEQ FCT_ID STRING COLOR BOOLEAN NIL ID
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
