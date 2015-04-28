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

		auto f = make_shared<UserFunction>(nullptr);
		auto breed = world->createBreed(f);
		breed->createTurtle();
	}

	WorldPtr WorldInterpreter::getWorld() {
		return world;
	}

	void WorldInterpreter::run() {
		if (world == nullptr )
			return;

		if (tree == nullptr )
			return;

		auto turtles = world->getTurtles();
		auto turtle_i = turtles.begin();
		interpret(*turtle_i, tree,make_shared<Table>());
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
