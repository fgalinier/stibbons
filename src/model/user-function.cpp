#include "user-function.h"

#include "../interpreter/interpreter.h"

namespace stibbons {

UserFunction::UserFunction (TreePtr tree, vector<string> params) :
	Function(params),
	tree(tree) {}

ValuePtr UserFunction::exec (AgentPtr agent, TablePtr params) {
	return Interpreter().interpret (agent, tree, params);
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
