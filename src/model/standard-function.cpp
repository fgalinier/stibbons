#include "standard-function.h"

#include "number.h"

#include <cstdlib>

namespace stibbons {

Value* RandFunction::exec (Agent* agent, Table* params) {
	return new Number(rand());
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
