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

#include "type.h"

#include <stdexcept>

namespace stibbons {

std::string toString(Type& type) {
	switch (type) {
		case Type::NIL:
			return "nil";
		case Type::NUMBER:
			return "number";
		case Type::BOOLEAN:
			return "boolean";
		case Type::STRING:
			return "string";
		case Type::COLOR:
			return "color";
		case Type::TABLE:
			return "table";
		case Type::FUNCTION:
			return "function";
		case Type::AGENT:
			return "agent";
		case Type::TURTLE:
			return "turtle";
		case Type::TYPE:
			return "type";
		case Type::ZONE:
			return "zone";
		case Type::WORLD:
			return "world";
		default:
			throw std::domain_error("Can't convert unknown type to string");
	}
}

std::string toString(Type&& type) {
	switch (type) {
		case Type::NIL:
			return "nil";
		case Type::NUMBER:
			return "number";
		case Type::BOOLEAN:
			return "boolean";
		case Type::STRING:
			return "string";
		case Type::COLOR:
			return "color";
		case Type::TABLE:
			return "table";
		case Type::FUNCTION:
			return "function";
		case Type::TURTLE:
			return "turtle";
		case Type::TYPE:
			return "type";
		case Type::ZONE:
			return "zone";
		case Type::WORLD:
			return "world";
		default:
			throw std::domain_error("Can't convert unknown type to string");
	}
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
