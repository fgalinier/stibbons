#include "number.h"

#include <cmath>
#include <sstream>

using namespace std;

namespace stibbons {

void Number::reset () {
	value = 0.0;
}

ValuePtr Number::add (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::NUMBER:
			return add (dynamic_pointer_cast<Number>(other));
		default:
			return Value::add(other);
	}
}

NumberPtr Number::add (NumberPtr other) {
	return make_shared<Number>(getValue() + other->getValue());
}

ValuePtr Number::substract (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::NUMBER:
			return substract (dynamic_pointer_cast<Number>(other));
		default:
			return Value::substract(other);
	}
}

NumberPtr Number::substract (NumberPtr other) {
	return make_shared<Number>(getValue() - other->getValue());
}

ValuePtr Number::multiply (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::NUMBER:
			return multiply (dynamic_pointer_cast<Number>(other));
		default:
			return Value::multiply(other);
	}
}

NumberPtr Number::multiply (NumberPtr other) {
	return make_shared<Number>(getValue() * other->getValue());
}

ValuePtr Number::divide (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::NUMBER:
			return divide (dynamic_pointer_cast<Number>(other));
		default:
			return Value::divide(other);
	}
}

NumberPtr Number::divide (NumberPtr other) throw(std::domain_error) {
	auto number = other->getValue();
	if (number == 0.0)
		throw std::domain_error("Can't divide by 0");

	return make_shared<Number>(getValue() / other->getValue());
}

ValuePtr Number::modulo (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::NUMBER:
			return modulo (dynamic_pointer_cast<Number>(other));
		default:
			return Value::modulo(other);
	}
}

NumberPtr Number::modulo (NumberPtr other) throw(std::domain_error) {
	auto number = other->getValue();
	if (number == 0.0)
		throw std::domain_error("Can't divide by 0");

	return make_shared<Number>(fmod(getValue(), other->getValue()));
}

int Number::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Number>(other));
}

int Number::compare(NumberPtr other) {
	return getValue () - other->getValue ();
}

string Number::toString () {
	std::ostringstream oss;

	oss << getValue();

	return oss.str();
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
