#include "boolean.h"

namespace stibbons {

Boolean::Boolean (bool value) : value(value) {}

void Boolean::setValue (bool new_var) {
	value = new_var;
}

bool Boolean::getValue () const {
	return value;
}

Type Boolean::getType() const {
	return Type::BOOLEAN;
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