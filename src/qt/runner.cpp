/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file runner.cpp
 * \brief Run Stibbons code in its own thread
 * \author Adrien Plazas
 * \version 1.1
 * \date 25/03/2015
 */

#include "runner.h"

#include "../interpreter/semantic-exception.h"

#include <sstream>
#include <iostream>

using namespace std;

namespace stibbons {

Runner::Runner(std::string& program) : started(false), running(false) {
	manager = new InterpreterManager(program);
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
	started = true;
	running = true;
	manager->onErrors([this](string type, string what) {
		emit error(QString(type.c_str()), QString(what.c_str()));
	});
	manager->run();
}

string Runner::exportModel() {
	lock_guard<recursive_mutex> lock(haltMutex);

	bool restart = isRunning();

	if (restart)
		halt();

	ostringstream oss;
	json_spirit::write_formatted(getWorld()->exportWorld(), oss);

	if (restart)
		unhalt();

	return oss.str();
}

bool Runner::isRunning() {
	return running;
}

void Runner::halt() {
	lock_guard<recursive_mutex> lock(haltMutex);

	if (manager) {
		manager->halt();
		running = false;
	}
}

void Runner::unhalt() {
	lock_guard<recursive_mutex> lock(haltMutex);

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
