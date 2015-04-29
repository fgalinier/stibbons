#include "type.h"

#include <stdexcept>

namespace stibbons {

std::string toString(Type& type) {
	switch (type) {
		case Type::NIL:
			return "Nil";
		case Type::NUMBER:
			return "Number";
		case Type::BOOLEAN:
			return "Boolean";
		case Type::STRING:
			return "String";
		case Type::COLOR:
			return "Color";
		case Type::TABLE:
			return "Table";
		case Type::FUNCTION:
			return "Function";
		case Type::TURTLE:
			return "Turtle";
		case Type::TYPE:
			return "Type";
		case Type::ZONE:
			return "Zone";
		case Type::WORLD:
			return "World";
		default:
			throw std::domain_error("Can't convert unknown type to string");
	}
}

std::string toString(Type&& type) {
	switch (type) {
		case Type::NIL:
			return "Nil";
		case Type::NUMBER:
			return "Number";
		case Type::BOOLEAN:
			return "Boolean";
		case Type::STRING:
			return "String";
		case Type::COLOR:
			return "Color";
		case Type::TABLE:
			return "Table";
		case Type::FUNCTION:
			return "Function";
		case Type::TURTLE:
			return "Turtle";
		case Type::TYPE:
			return "Type";
		case Type::ZONE:
			return "Zone";
		case Type::WORLD:
			return "World";
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
