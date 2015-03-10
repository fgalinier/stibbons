#include "line.h"

namespace stibbons {

void Line::setColor (Color color) {
	this->color = color;
}

Color& Line::getColor () {
	return color;
}

const Color& Line::getColor () const {
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
