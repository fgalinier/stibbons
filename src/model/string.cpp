/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "string.h"

using namespace std;

namespace stibbons {

void String::reset () {
	value = "";
}

ValuePtr String::add (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::STRING:
			return add (dynamic_pointer_cast<String>(other));
		default:
			return Value::add(other);
	}
}

StringPtr String::add (StringPtr other) {
	return make_shared<String>(getValue() + other->getValue());
}

double String::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<String>(other));
}

double String::compare(StringPtr other) {
	if (getValue () < other->getValue () )
		return -1;
	if (getValue () > other->getValue () )
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
