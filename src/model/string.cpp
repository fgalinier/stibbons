#include "string.h"

using namespace std;

namespace stibbons {

void String::reset () {
	value = "";
}

int String::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<String>(other));
}

int String::compare(StringPtr other) {
	if (other->getValue () < getValue ())
		return -1;
	if (other->getValue () > getValue ())
		return 1;
	return 0;
}

string String::toString () {
	return getValue();
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
