#include "world-interpreter.h"

#include <cstring>

#include "../model/turtle.h"
#include "../model/user-function.h"

extern FILE *yyin;

namespace stibbons {

	WorldInterpreter::WorldInterpreter(const char *program) throw(SyntaxException) {
		size_t size = strlen(program);

		// Copy the string to make it non-constant
		void *buffer = malloc(size);
		memcpy(buffer, program, size);

		// Create a new file stream for the program string
		FILE *file = fmemopen(buffer, size, "r+");
		yyin = file;

		// Parse the program
		tree = make_shared<Tree>(0,nullptr);
		yy::parser* pparser = new yy::parser(tree);
		pparser->parse();

		// Destroy the file stream and the buffer
		fclose(file);
		free(buffer);

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
