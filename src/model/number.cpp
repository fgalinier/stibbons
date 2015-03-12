#include "number.h"

namespace stibbons {

Number::Number (double value) : value(value) {}

Type Number::getType() const{
	return Type::NUMBER;
}

void Number::setValue (double new_var) {
	value = new_var;
}

double Number::getValue () {
	return value;
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
