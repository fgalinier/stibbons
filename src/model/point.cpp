#include "point.h"

namespace stibbons {

static const string invalidAxisMessage = "This point doesn't have the requested axis";

Point::Point (unsigned dimensions) : dimensions(dimensions) {
	axes = new double[dimensions]();
}

Point::Point (const Point &point) : dimensions(point.getDimensions()) {
	axes = new double[getDimensions()]();
	for (unsigned i = 0 ; i < getDimensions() ; i++)
		setValue(i, point.getValue(i));
}

void Point::setValue (unsigned axis, double value) throw(out_of_range) {
	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	axes[axis] = value;
}

double& Point::getValue (unsigned axis) throw(out_of_range) {
	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	return axes[axis];
}

const double& Point::getValue (unsigned axis) const throw(out_of_range) {
	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	return axes[axis];
}

unsigned Point::getDimensions () const {
	return dimensions;
}

double& Point::operator[] (unsigned axis) throw(out_of_range) {
	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	return axes[axis];
}

const double& Point::operator[] (unsigned axis) const throw(out_of_range) {
	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	return axes[axis];
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
