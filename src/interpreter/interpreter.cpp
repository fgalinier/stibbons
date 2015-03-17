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
			case yy::parser::token::FD: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				turtle->forward(((Number*) val)->getValue());
			}
				break;
			case yy::parser::token::RT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				turtle->turnRight(((Number*) val)->getValue());
			}
				break;
			case yy::parser::token::LT: {
				auto val = this->interpret(tree->getSon(0));
				if(val->getType() != Type::NUMBER) throw std::exception();
				turtle->turnLeft(((Number*) val)->getValue());
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
			case '+': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				return new Number((((Number*) val1)->getValue())+(((Number*) val2)->getValue()));
			}
				break;
			case '-': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				return new Number((((Number*) val1)->getValue())-(((Number*) val2)->getValue()));
			}
				break;
			case '*': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				return new Number((((Number*) val1)->getValue())*(((Number*) val2)->getValue()));
			}
				break;
			case '/': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				if(((Number*) val2)->getValue() == 0) 
					throw std::exception();
				return new Number((((Number*) val1)->getValue())/(((Number*) val2)->getValue()));
			}
				break;
			case '%': {
				auto val1 = this->interpret(tree->getSon(0));
				auto val2 = this->interpret(tree->getSon(1));
				if(val1->getType() != Type::NUMBER || val2->getType() != Type::NUMBER) 
					throw std::exception();
				if(((Number*) val2)->getValue() == 0) 
					throw std::exception();
				return new Number(((int) ((Number*) val1)->getValue())%((int) ((Number*) val2)->getValue()));
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
