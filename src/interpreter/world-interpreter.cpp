#include "world-interpreter.h"
#include "parser.h"

#include <cstring>
#include <sstream>

#include "../model/turtle.h"
#include "../model/user-function.h"

namespace stibbons {

	WorldInterpreter::WorldInterpreter(std::string program) throw(InterpreterException) {
		std::istringstream iss(program, ios_base::in);

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

	WorldPtr WorldInterpreter::getWorld() {
		return world;
	}

	ValuePtr WorldInterpreter::interpret(AgentPtr agent,
									   const TreePtr tree,
									   TablePtr hashTable)  throw(SemanticException) {
		if(agent->getType() == Type::WORLD)
			return this->interpret(dynamic_pointer_cast<World>(agent),tree,hashTable);

		throw SemanticException("Invalid action for the world",getPosition(tree));
	}

	ValuePtr WorldInterpreter::interpret(WorldPtr agent,
									   const TreePtr tree,
									   TablePtr hashTable)  throw(SemanticException) {
		ValuePtr start = Interpreter::interpret(agent,tree,hashTable);

		if(start != nullptr)	
			return start;

		throw SemanticException("Invalid action for the world",getPosition(tree));		
	}

	void WorldInterpreter::run() {
		if (world == nullptr )
			return;

		if (tree == nullptr )
			return;

		WorldInterpreter::start(world,tree);
	}

	void WorldInterpreter::halt() {
		std::unique_lock<std::mutex> lock(suspendMutex);
		  suspendFlag = true;
	}

	void WorldInterpreter::unhalt() {
		std::unique_lock<std::mutex> lock(suspendMutex);
		suspendFlag = false;
		resumeCond.notify_all();
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
