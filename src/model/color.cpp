#include "color.h"

#include <cerrno>
#include <cstring>

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
