#include "type-value.h"

using namespace std;

namespace stibbons {

void TypeValue::reset () {
	value = Type::TYPE;
}

double TypeValue::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<TypeValue>(other));
}

double TypeValue::compare(TypeValuePtr other) {
	return (long) getValue () - (long) other->getValue ();
}

string TypeValue::toString () {
	return stibbons::toString(getValue());
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
