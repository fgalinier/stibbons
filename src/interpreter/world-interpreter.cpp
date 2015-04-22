#include "world-interpreter.h"
#include "parser.h"

#include <cstring>
#include <sstream>

#include "../model/turtle.h"
#include "../model/user-function.h"

namespace stibbons {

	WorldInterpreter::WorldInterpreter(std::string program) throw(SyntaxException) {
		std::istringstream iss(program, ios_base::in);

		// Parse the program
		tree = make_shared<Tree>(0,nullptr);
		Parser pparser(tree, &iss);
		pparser.parse();

		// Create a new world depending on the program's parameters
		auto worldSize = Size(2);
		worldSize.setValue(0, 50);
		worldSize.setValue(1, 50);
		auto zoneSize = Size(2);
		zoneSize.setValue(0, 10);
		zoneSize.setValue(1, 10);
		auto warp = vector<bool>();
		warp.push_back(false);
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
		// TODO mettre en pause l'exécution
	}

	void WorldInterpreter::unhalt() {
		// TODO reprend l'exécution
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
