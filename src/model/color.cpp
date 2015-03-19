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
	red = truncate(r);
}

void Color::g (double g){
	green = truncate(g);
}

void Color::b (double b){
	blue = truncate(b);
}

double Color::r () const {
	return red;
}

double Color::g () const {
	return green;
}

double Color::b () const {
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
