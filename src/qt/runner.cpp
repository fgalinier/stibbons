/**
 * \file runner.cpp
 * \brief Run Stibbons code in its own thread
 * \author Adrien Plazas
 * \version 0.4
 * \date 25/03/2015
 */

#include "runner.h"

#include "../interpreter/semantic-exception.h"

#include <iostream>

using namespace std;

namespace stibbons {

Runner::Runner(std::string& program) : started(false), running(false) {
	try {
		manager = new InterpreterManager(program);
	}
	catch (SemanticException e) {
		cerr << "Semantic error: " << e.what() << endl;
	}
	catch (SyntaxException e) {
		cerr << "Syntax error: " << e.what() << endl;
	}
	catch (exception e) {
		cerr << e.what() << endl;
	}
}

Runner::~Runner() {
	delete manager;
}

WorldPtr Runner::getWorld() {
	return manager->getWorld();
}

void Runner::start() {
	if (started)
		unhalt();
	else {
		started = true;
		running = true;
		QThread::start();
	}
}

void Runner::run() {
	try {
		started = true;
		running = true;
		manager->run();
	}
	catch (SemanticException e) {
		halt();
		emit error("Semantic error", QString(e.what()));
		running = false;
	}
	catch (exception e) {
		halt();
		emit error("Error", QString(e.what()));
		running = false;
	}
}

bool Runner::isRunning() {
	return running;
}

void Runner::halt() {
	if (manager) {
		manager->halt();
		running = false;
	}
}

void Runner::unhalt() {
	if (manager) {
		manager->unhalt();
		running = true;
	}
}

void Runner::setWaitTime(size_t waitTime) {
	manager->setWaitTime(waitTime);
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
