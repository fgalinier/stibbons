/**
 * \file runner.cpp
 * \brief Run Stibbons code in its own thread
 * \author Adrien Plazas
 * \version 0.4
 * \date 25/03/2015
 */

#include "runner.h"

#include <iostream>

using namespace std;

namespace stibbons {

Runner::Runner(std::string& program) {
	try {
		interpreter = new WorldInterpreter(program.c_str());
	}
	catch (SyntaxException e) {
		cerr << "Syntax error: " << e.what() << endl;
	}
	catch (exception e) {
		cerr << e.what() << endl;
	}
}

Runner::~Runner() {
	delete interpreter;
}

WorldPtr Runner::getWorld() {
	return interpreter->getWorld();
}

void Runner::run() {
	try {
		interpreter->run();
	}
	catch (SemanticException e) {
		cerr << "Semantic error: " << e.what() << endl;
	}
	catch (exception e) {
		cerr << e.what() << endl;
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
