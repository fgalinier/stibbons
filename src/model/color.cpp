#include "color.h"

#include <cerrno>
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;

namespace stibbons {

/**
 * Check whether a value is between 0 and 1 and put it truncated to fit
 * in these boundaries.
 */
inline double truncate (double value) {
	if (value <= 0.0)
		return 0.0;

	if (value >= 1.0)
		return 1.0;

	return value;
}

Color::Color(double red, double green, double blue) {
	r(red);
	g(green);
	b(blue);
}

Color::Color(Color& other) {
	lock_guard<mutex> lock(other.value_m);

	// Set this
	red   = other.red;
	green = other.green;
	blue  = other.blue;
}

Color::Color (Color&& other) {
	lock_guard<mutex> lock(other.value_m);

	// Set this
	red   = other.red;
	green = other.green;
	blue  = other.blue;

	// Reset other
	other.red   = 0.0;
	other.green = 0.0;
	other.blue  = 0.0;
}

Color& Color::operator= (Color& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<mutex> self_lock(value_m, adopt_lock);
	lock_guard<mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	red   = other.red;
	green = other.green;
	blue  = other.blue;

	return *this;
}

Color& Color::operator= (Color&& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<mutex> self_lock(value_m, adopt_lock);
	lock_guard<mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	red   = other.red;
	green = other.green;
	blue  = other.blue;

	// Reset other
	other.red   = 0.0;
	other.green = 0.0;
	other.blue  = 0.0;

	return *this;
}

Color::Color (string color) throw(domain_error) {
	auto str = color.c_str() + 1;

	int bps;    // bits per sample
	double max; // maximum value (2^bps - 1)
	long mask;  // a sample

	switch (strlen (str)) {
		case 6:
			bps = 8;
			max = 255.0;
			mask = 0xFF;
			break;
		case 3:
			bps = 4;
			max = 15.0;
			mask = 0xF;
			break;
		default:
			throw domain_error("Not a color: " + color);
	}

	auto value = strtol(str, NULL, 16);
	auto error = errno;
	if (error)
		throw domain_error("Not a color: " + color);
	// si erreur = EINVAL, exception
	// ERANGE

	r(((value >> (2*bps)) & mask) / max);
	g(((value >>    bps ) & mask) / max);
	b(( value             & mask) / max);
}

void Color::r (double r){
	lock_guard<mutex> lock(value_m);
	red = truncate(r);
}

void Color::g (double g){
	lock_guard<mutex> lock(value_m);
	green = truncate(g);
}

void Color::b (double b){
	lock_guard<mutex> lock(value_m);
	blue = truncate(b);
}

double Color::r () {
	lock_guard<mutex> lock(value_m);
	return red;
}

double Color::g () {
	lock_guard<mutex> lock(value_m);
	return green;
}

double Color::b () {
	lock_guard<mutex> lock(value_m);
	return blue;
}

ValuePtr Color::add (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::COLOR:
			return add (dynamic_pointer_cast<Color>(other));
		default:
			return Value::add(other);
	}
}

ColorPtr Color::add (ColorPtr other) {
	return make_shared<Color>(r() + other->r(),
	                          g() + other->g(),
	                          b() + other->b());
}

ValuePtr Color::substract (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::COLOR:
			return substract (dynamic_pointer_cast<Color>(other));
		default:
			return Value::substract(other);
	}
}

ColorPtr Color::substract (ColorPtr other) {
	return make_shared<Color>(r() - other->r(),
	                          g() - other->g(),
	                          b() - other->b());
}

ValuePtr Color::multiply (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::COLOR:
			return multiply (dynamic_pointer_cast<Color>(other));
		default:
			return Value::multiply(other);
	}
}

ColorPtr Color::multiply (ColorPtr other) {
	return make_shared<Color>(r() * other->r(),
	                          g() * other->g(),
	                          b() * other->b());
}

ValuePtr Color::divide (ValuePtr other) throw(std::domain_error) {
	switch (other->getType()) {
		case Type::COLOR:
			return divide (dynamic_pointer_cast<Color>(other));
		default:
			return Value::divide(other);
	}
}

ColorPtr Color::divide (ColorPtr other) {
	auto red   = other->r();
	auto green = other->g();
	auto blue  = other->b();

	return make_shared<Color>(red   != 0.0 ? r() * red   : 1.0,
	                          green != 0.0 ? r() * green : 1.0,
	                          blue  != 0.0 ? r() * blue  : 1.0);
}

int Color::compare (ValuePtr other) {
	if (getType() != other->getType())
		return Value::compare (other);

	return compare (dynamic_pointer_cast<Color>(other));
}

int Color::compare (ColorPtr other) {
	auto red = r() - other->r();
	if (red < 0.0) return -1;
	if (red > 0.0) return 1;

	auto green = g() - other->g();
	if (green < 0.0) return -1;
	if (green > 0.0) return 1;

	auto blue = b() - other->b();
	if (blue < 0.0) return -1;
	if (blue > 0.0) return 1;

	return 0;
}

string Color::toString () {
	std::ostringstream oss;

	long _r = (long) (r() * 255);
	long _g = (long) (g() * 255);
	long _b = (long) (b() * 255);
	long color = (_r << 16) + (_g << 8) + _b;

	oss << "#"
	    << std::setfill ('0') << std::setw(6)
	    << std::hex << color;

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
