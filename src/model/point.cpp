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

#include "point.h"

#include <cmath>
#include <cstring>

namespace stibbons {

static const string invalidAxisMessage = "This point doesn't have the requested axis";

Point::Point (unsigned dimensions) : dimensions(dimensions) {
	axes = new double[dimensions]();
}

Point::Point(Point& other) {
	lock_guard<recursive_mutex> lock(other.value_m);

	// Set this
	dimensions = other.dimensions;
	axes = new double[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(double));
}

Point::Point (Point&& other) {
	lock_guard<recursive_mutex> lock(other.value_m);

	// Set this
	dimensions = move(other.dimensions);
	axes = new double[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(double));

	// Reset other
	other.dimensions = 0;
	if (other.axes)
		delete[] other.axes;
	other.axes = nullptr;
}

Point& Point::operator= (Point& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
	lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	dimensions = other.dimensions;
	if (axes)
		delete[] axes;
	axes = new double[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(double));

	return *this;
}

Point& Point::operator= (Point&& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
	lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	dimensions = other.dimensions;
	if (axes)
		delete[] axes;
	axes = new double[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(double));

	// Reset other
	other.dimensions = 0;
	if (other.axes)
		delete[] other.axes;
	other.axes = nullptr;

	return *this;
}

Point::~Point () {
	if (axes)
		delete[] axes;
}

void Point::setValue (unsigned axis, double value) throw(out_of_range) {
	lock_guard<recursive_mutex> lock(value_m);

	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	axes[axis] = value;
}

double Point::getValue (unsigned axis) throw(out_of_range) {
	lock_guard<recursive_mutex> lock(value_m);

	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	return axes[axis];
}

unsigned Point::getDimensions () const {
	return dimensions;
}

Point Point::getClosestImage (Point& other, Size& environment, vector<BorderType> borderTypes) {
	auto dimensions = other.getDimensions();

	auto image = Point(dimensions);

	for (size_t i = 0 ; i < dimensions ; i++) {
		double value = other.getValue(i);

		// If a wrap is possible, get the image's value
		if (borderTypes[i] == BorderType::WRAP) {
			// Compute the images' values deltas to this point's
			double c = getValue(i) - other.getValue(i);
			double l = c + environment[i];
			double r = c - environment[i];

			// Keep the smallest delta
			double delta = abs(l) < abs(r) ? l : r;
			delta = abs(c) < abs(delta) ? c : delta;

			// Update the image's value
			value = getValue(i) - delta;
		}

		image.setValue(i, value);
	}

	return image;
}

double Point::getDistanceTo (Point& other) {
	lock_guard<recursive_mutex> self_lock(value_m);
	lock_guard<recursive_mutex> other_lock(other.value_m);

	double x = other.getValue(0) - getValue(0);
	double y = other.getValue(1) - getValue(1);

	return sqrt (x * x + y * y);
}

double Point::getAngleTo (Point& other) {
	lock_guard<recursive_mutex> self_lock(value_m);
	lock_guard<recursive_mutex> other_lock(other.value_m);

	double x = other.getValue(0) - getValue(0);
	double y = other.getValue(1) - getValue(1);

	return atan2 (y, x);
}

bool Point::warp (Size& environment, vector<BorderType> borderTypes) {
	bool warped = false;

	for (size_t axis = 0 ; axis < getDimensions() ; axis++)
		if (borderTypes[axis] == BorderType::WRAP) {
			size_t max = environment.getValue(axis);
			auto value = getValue(axis);
			if ((value >= max) | (value < 0))
				warped = true;
			while (value >= max)
				value -= max;
			while (value < 0)
				value += max;
			setValue(axis, value);
		}

	return warped;
}

double Point::operator[] (unsigned axis) throw(out_of_range) {
	lock_guard<recursive_mutex> lock(value_m);

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
