/**
 * \file runner.cpp
 * \brief Run Stibbons code in its own thread
 * \author Adrien Plazas
 * \version 0.3
 * \date 25/03/2015
 */

#include "runner.h"

#include <iostream>
namespace stibbons {

Runner::Runner(std::string& program) {
	interpreter = new WorldInterpreter(program.c_str());
}

Runner::~Runner() {
	delete interpreter;
}

World* Runner::getWorld() {
	return interpreter->getWorld();
}

void Runner::run() {
	interpreter->run();
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
