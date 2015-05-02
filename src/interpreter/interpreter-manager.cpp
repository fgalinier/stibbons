#include "interpreter-manager.h"

#include "parser.h"
#include "world-interpreter.h"

#include "../model/user-function.h"

using namespace std;

namespace stibbons {

yy::position InterpreterManager::getPosition(const TreePtr tree) {
	return yy::position(nullptr,
	                    get<0>(tree->getPosition()),
	                    get<0>(tree->getPosition()));
}

InterpreterManager::InterpreterManager(string program) throw(InterpreterException) :
	errorCallback(nullptr),
	suspendFlag(false),
	exitFlag(false) {
	istringstream iss(program, ios_base::in);

	// Parse the program
	tree = make_shared<Tree>(0,nullptr);
	auto worldDir = make_shared<Table>();
	Parser pparser(tree, worldDir, &iss);
	pparser.parse();

	// Create a new world depending on the program's parameters
	ValuePtr prop;
	auto worldSize = Size(2);

	if ((prop = worldDir->getValue("world-width")) != Nil::getInstance()) {
		if (prop->getType() != Type::NUMBER) {
			throw SemanticException("%world-width",
									Type::NUMBER,
									prop->getType(),
									getPosition(tree));
		}
		worldSize.setValue(0, dynamic_pointer_cast<Number>(prop)->getValue());
	}
	else
		worldSize.setValue(0, 50);

	if ((prop = worldDir->getValue("world-height")) != Nil::getInstance()) {
		if (prop->getType() != Type::NUMBER) {
			throw SemanticException("%world-height",
									Type::NUMBER,
									prop->getType(),
									getPosition(tree));
		}
		worldSize.setValue(1, dynamic_pointer_cast<Number>(prop)->getValue());
	}
	else
		worldSize.setValue(1, 50);

	auto zoneSize = Size(2);

	if ((prop = worldDir->getValue("zone-width")) != Nil::getInstance()) {
		if (prop->getType() != Type::NUMBER) {
			throw SemanticException("%zone-width",
									Type::NUMBER,
									prop->getType(),
									getPosition(tree));
		}
		zoneSize.setValue(0, dynamic_pointer_cast<Number>(prop)->getValue());
	}
	else
		zoneSize.setValue(0, 10);

	if ((prop = worldDir->getValue("zone-height")) != Nil::getInstance()) {
		if (prop->getType() != Type::NUMBER) {
			throw SemanticException("%zone-height",
									Type::NUMBER,
									prop->getType(),
									getPosition(tree));
		}
		zoneSize.setValue(1, dynamic_pointer_cast<Number>(prop)->getValue());
	}
	else
		zoneSize.setValue(1, 10);

	auto warp = vector<bool>();

	if ((prop = worldDir->getValue("x-warp")) != Nil::getInstance()) {
		if (prop->getType() != Type::BOOLEAN) {
			throw SemanticException("%x-warp",
									Type::BOOLEAN,
									prop->getType(),
									getPosition(tree));
		}
		warp.push_back(dynamic_pointer_cast<Boolean>(prop)->getValue());
	}
	else
		warp.push_back(false);

	if ((prop = worldDir->getValue("y-warp")) != Nil::getInstance()) {
		if (prop->getType() != Type::BOOLEAN) {
			throw SemanticException("%y-warp",
									Type::BOOLEAN,
									prop->getType(),
									getPosition(tree));
		}
		warp.push_back(dynamic_pointer_cast<Boolean>(prop)->getValue());
	}
	else
		warp.push_back(false);

	world = World::construct(worldSize, zoneSize, warp);
}

InterpreterManager::~InterpreterManager() {
	stop();
}

WorldPtr InterpreterManager::getWorld() {
	return world;
}

void InterpreterManager::onErrors (std::function<void(string,string)> callback) {
	errorCallback = callback;
}

void InterpreterManager::errorsOccured (string type, string what) {
	if (errorCallback)
		errorCallback(type, what);
}

void InterpreterManager::stop () {
	if (!exitFlag) {
		exitFlag = true;
		suspendFlag = false;
		suspendMutex.unlock();
		for (auto i : interpreters) {
			try {
				i.second->join();
			}
			catch (exception e) {}
		}
	}
}

void InterpreterManager::run() {
	if (world == nullptr )
		return;

	if (tree == nullptr )
		return;

	try {
		WorldInterpreter wi;
		wi.interpret(*this, world, tree, make_shared<Table>());
	}
	catch (exit_requested_exception e) {
		stop();
	}
	catch (SemanticException e) {
		stop();
		errorsOccured("Semantic error", string(e.what()));
	}
	catch (SyntaxException e) {
		stop();
		errorsOccured("Syntax error", string(e.what()));
	}
	catch (exception e) {
		stop();
		errorsOccured("Unknown error", string(e.what()));
	}
}

void InterpreterManager::wait() {
	this_thread::sleep_for(chrono::microseconds(waitTime));
}

void InterpreterManager::setWaitTime(size_t waitTime) {
	this->waitTime = waitTime;
}

void InterpreterManager::checkHalt() {
	if (exitFlag)
		return;

	if (suspendFlag)
		lock_guard<mutex> lock(suspendMutex);
}

void InterpreterManager::checkExit() throw(exit_requested_exception) {
	if (exitFlag)
		throw exit_requested_exception();
}

void InterpreterManager::halt() {
	if (exitFlag)
		return;

	if (!suspendFlag)
		suspendMutex.lock();

	suspendFlag = true;
}

void InterpreterManager::unhalt() {
	if (exitFlag)
		return;

	if (suspendFlag)
		suspendMutex.unlock();

	suspendFlag = false;
}

void InterpreterManager::interpret(shared_ptr<Interpreter> interpreter,
               FunctionPtr function,
               AgentPtr agent,
               TablePtr params) {
	try {
		interpreter->interpretFunction(function, agent, params);
	}
	catch (exit_requested_exception e) {
		stop();
	}
	catch (SemanticException e) {
		stop();
		errorsOccured("Semantic error", string(e.what()));
	}
	catch (SyntaxException e) {
		stop();
		errorsOccured("Syntax error", string(e.what()));
	}
	catch (exception e) {
		stop();
		errorsOccured("Unknown error", string(e.what()));
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
