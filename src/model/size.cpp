#include "size.h"

#include <cstring>

namespace stibbons {

static const string invalidAxisMessage = "This size doesn't have the requested axis";

Size::Size (unsigned dimensions) : dimensions(dimensions) {
	axes = new size_t[dimensions]();
}

Size::Size(Size& other) {
	lock_guard<recursive_mutex> lock(other.value_m);

	// Set this
	dimensions = other.dimensions;
	axes = new size_t[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(size_t));
}

Size::Size (Size&& other) {
	lock_guard<recursive_mutex> lock(other.value_m);

	// Set this
	dimensions = move(other.dimensions);
	axes = new size_t[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(size_t));

	// Reset other
	other.dimensions = 0;
	if (other.axes)
		delete[] other.axes;
	other.axes = nullptr;
}

Size& Size::operator= (Size& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
	lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	dimensions = other.dimensions;
	if (axes)
		delete[] axes;
	axes = new size_t[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(size_t));

	return *this;
}

Size& Size::operator= (Size&& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<recursive_mutex> self_lock(value_m, adopt_lock);
	lock_guard<recursive_mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	dimensions = other.dimensions;
	if (axes)
		delete[] axes;
	axes = new size_t[dimensions]();
	memcpy(axes, other.axes, dimensions * sizeof(size_t));

	// Reset other
	other.dimensions = 0;
	if (other.axes)
		delete[] other.axes;
	other.axes = nullptr;

	return *this;
}

Size::~Size () {
	if (axes)
		delete[] axes;
}

void Size::setValue (unsigned axis, size_t value) throw(out_of_range) {
	lock_guard<recursive_mutex> lock(value_m);

	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	axes[axis] = value;
}

size_t Size::getValue (unsigned axis) throw(out_of_range) {
	lock_guard<recursive_mutex> lock(value_m);

	if (axis >= dimensions)
		throw out_of_range(invalidAxisMessage);

	return axes[axis];
}

unsigned Size::getDimensions () const {
	return dimensions;
}

size_t Size::operator[] (unsigned axis) throw(out_of_range) {
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
