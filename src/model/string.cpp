#include "string.h"

using namespace std;

namespace stibbons {

String::String (string s) : value(s) {}

Type String::getType () const {
	return Type::STRING;
}

string String::getValue () {
	return value;
}

void String::setValue (string new_var) {
	value = new_var;
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
