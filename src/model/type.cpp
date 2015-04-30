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
