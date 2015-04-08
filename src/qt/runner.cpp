/**
 * \file runner.cpp
 * \brief Run Stibbons code in its own thread
 * \author Adrien Plazas
 * \version 0.3
 * \date 25/03/2015
 */

#include "runner.h"

#include "../interpreter/interpreter.h"
#include <iostream>
namespace stibbons {

Runner::Runner(Turtle& turtle, std::string& program) : turtle(turtle), program(program) {}

void Runner::run() {
	auto interpreter = Interpreter(&turtle);
	auto tree = interpreter.parse(program.c_str());
	interpreter.interpret(tree);
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
