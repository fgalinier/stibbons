#include "user-function.h"

#include "type.h"
#include "../interpreter/world-interpreter.h"
#include "../interpreter/turtle-interpreter.h"

namespace stibbons {

UserFunction::UserFunction (InterpreterManager& manager, TreePtr tree, vector<string> params) :
	Function(params),
	manager(&manager),
	tree(tree) {}

UserFunction::UserFunction (TreePtr tree, vector<string> params) :
	Function(params),
	manager(nullptr),
	tree(tree) {}

ValuePtr UserFunction::exec (AgentPtr agent, TablePtr params) {
	switch (agent->getType()) {
		case Type::TURTLE:
			return TurtleInterpreter().interpret(*manager, agent, tree, params);
		case Type::WORLD:
			return TurtleInterpreter().interpret(*manager, agent, tree, params);
		default:
			return Interpreter().interpret(*manager, agent, tree, params);
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
