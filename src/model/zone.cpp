#include "zone.h"

namespace stibbons {

Zone::Zone () : color(Color(1.0, 1.0, 1.0)) {}

void Zone::setColor (Color color) {
	this->color = color;
}

Color& Zone::getColor () {
	return color;
}

const Color& Zone::getColor () const {
	return color;
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
