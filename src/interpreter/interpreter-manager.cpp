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

#include "interpreter-manager.h"

#include "parser.h"
#include "world-interpreter.h"

#include "../model/table.h"
#include "../model/border-type.h"
#include "../model/user-function.h"

#include <algorithm>

using namespace std;

namespace stibbons {

	bool InterpreterManager::suspendFlag;
	condition_variable InterpreterManager::resumeCond;

	yy::position InterpreterManager::getPosition(const TreePtr tree) {
		return yy::position(nullptr,
							get<0>(tree->getPosition()),
							get<0>(tree->getPosition()));
	}

	InterpreterManager::InterpreterManager(string program) throw(InterpreterException) :
		errorCallback(nullptr),	
		waitTime(0),
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

		if ((prop = worldDir->getValue("world_width")) != Nil::getInstance()) {
			if (prop->getType() != Type::NUMBER) {
				throw SemanticException("%world_width",
										Type::NUMBER,
										prop->getType(),
										getPosition(tree));
			}
			worldSize.setValue(0, dynamic_pointer_cast<Number>(prop)->getValue());
		}
		else
			worldSize.setValue(0, 50);

		if ((prop = worldDir->getValue("world_height")) != Nil::getInstance()) {
			if (prop->getType() != Type::NUMBER) {
				throw SemanticException("%world_height",
										Type::NUMBER,
										prop->getType(),
										getPosition(tree));
			}
			worldSize.setValue(1, dynamic_pointer_cast<Number>(prop)->getValue());
		}
		else
			worldSize.setValue(1, 50);

		auto zoneSize = Size(2);

		if ((prop = worldDir->getValue("zone_width")) != Nil::getInstance()) {
			if (prop->getType() != Type::NUMBER) {
				throw SemanticException("%zone_width",
										Type::NUMBER,
										prop->getType(),
										getPosition(tree));
			}
			zoneSize.setValue(0, dynamic_pointer_cast<Number>(prop)->getValue());
		}
		else
			zoneSize.setValue(0, 10);

		if ((prop = worldDir->getValue("zone_height")) != Nil::getInstance()) {
			if (prop->getType() != Type::NUMBER) {
				throw SemanticException("%zone_height",
										Type::NUMBER,
										prop->getType(),
										getPosition(tree));
			}
			zoneSize.setValue(1, dynamic_pointer_cast<Number>(prop)->getValue());
		}
		else
			zoneSize.setValue(1, 10);

		auto warp = vector<BorderType>();

		if ((prop = worldDir->getValue("x_border")) != Nil::getInstance()) {
			if (prop->getType() != Type::STRING) {
				throw SemanticException("%x_border expect a value in {NONE, BOUNCE, WRAP}",
										getPosition(tree));
			}
			auto val = dynamic_pointer_cast<String>(prop)->getValue();
			std::transform(val.begin(),val.end(),val.begin(),::tolower);
			
			BorderType b = BorderType::NONE;
			if(val == "none") ; 
			else if(val == "bounce")
				b = BorderType::BOUNCE;
			else if(val == "wrap")
				b = BorderType::WRAP;				
			else
				throw SemanticException("%x_border expect a value in {NONE, BOUNCE, WRAP}",
										getPosition(tree));

			warp.push_back(b);
		}
		else
			warp.push_back(BorderType::NONE);

		if ((prop = worldDir->getValue("y_border")) != Nil::getInstance()) {
			if (prop->getType() != Type::STRING) {
				throw SemanticException("%y_border expect a value in {NONE, BOUNCE, WRAP}",
										getPosition(tree));
			}
			auto val = dynamic_pointer_cast<String>(prop)->getValue();
			std::transform(val.begin(),val.end(),val.begin(),::tolower);
			
			BorderType b = BorderType::NONE;
			if(val == "none") ; 
			else if(val == "bounce")
				b = BorderType::BOUNCE;
			else if(val == "wrap")
				b = BorderType::WRAP;				
			else
				throw SemanticException("%y_border expect a value in {NONE, BOUNCE, WRAP}",
										getPosition(tree));

			warp.push_back(b);
		}
		else
			warp.push_back(BorderType::NONE);

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
			unhalt();
			stopMutex.unlock();
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

		interpret_async<WorldInterpreter>(
			make_shared<UserFunction> (*this, tree),
			world,
			make_shared<Table>()
		);
	}

	void InterpreterManager::wait() {
		this_thread::sleep_for(chrono::microseconds(waitTime));
	}

	void InterpreterManager::setWaitTime(size_t waitTime) {
		this->waitTime = waitTime;
	}

	void InterpreterManager::checkExit() throw(exit_requested_exception) {
		if (exitFlag)
			throw exit_requested_exception();
	}

	bool cond() {return !InterpreterManager::suspendFlag;}
	
	void InterpreterManager::checkHalt() {
		if(suspendFlag){
		   for(auto i : interpreters){
			   std::get<0>(i)->inPauseFlag = true;
			   std::unique_lock<std::mutex> lock(std::get<0>(i)->suspendMutex);
			   resumeCond.wait(lock,cond);
			   std::get<0>(i)->inPauseFlag = false;
		   }
		}
	}

	void InterpreterManager::halt() {
		if(exitFlag)
			return;

		if(suspendFlag)
			return;

		suspendFlag = true;
		for(auto i : interpreters){
			while(std::get<0>(i)->inPauseFlag);
		}
	}

	void InterpreterManager::unhalt() {
		suspendFlag = false;
		resumeCond.notify_all();
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
