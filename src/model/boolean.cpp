#include "boolean.h"

using namespace std;

namespace stibbons {

void Boolean::reset () {
	value = false;
}

int Boolean::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Boolean>(other));
}

int Boolean::compare(BooleanPtr other) {
	return other->getValue () - getValue ();
}

string Boolean::toString () {
	return getValue() ? "true" : "false";
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
