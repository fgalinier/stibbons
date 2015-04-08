#include "number.h"

#include <sstream>

using namespace std;

namespace stibbons {

void Number::reset () {
	value = 0.0;
}

string Number::toString () {
	std::ostringstream oss;

	oss << getValue();

	return oss.str();
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
