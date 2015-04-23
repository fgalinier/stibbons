#include "line.h"

namespace stibbons {

Line::Line(Point point) {
	push_back(point);
}

Line::Line(Line& other, size_t since) {
	lock_guard<mutex> lock(other.value_m);

	// Set this
	color = other.color;
	for (size_t i = since ; i < other.points.size() ; i++)
		points.push_back(Point(other.points[i]));
}

Line::Line (Line&& other) {
	lock_guard<mutex> lock(other.value_m);

	// Set this
	color = move(other.color);
	points = move(other.points);

	// Reset other
	other.color = Color();
	other.points = vector<Point>();
}

Line& Line::operator= (Line& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<mutex> self_lock(value_m, adopt_lock);
	lock_guard<mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	color = other.color;
	for (auto& p: other.points) {
		points.push_back(Point(p));
	}

	return *this;
}

Line& Line::operator= (Line&& other) {
	if (this == &other)
		return *this;

	lock(value_m, other.value_m);
	lock_guard<mutex> self_lock(value_m, adopt_lock);
	lock_guard<mutex> other_lock(other.value_m, adopt_lock);

	// Set this
	color = move(other.color);
	points = move(other.points);

	// Reset other
	other.color = Color();
	other.points = vector<Point>();

	return *this;
}

void Line::setColor (Color color) {
	this->color = color;
}

Color& Line::getColor () {
	return color;
}

const Color& Line::getColor () const {
	return color;
}

void Line::push_back (Point point) {
	lock_guard<mutex> lock(value_m);

	points.push_back(Point(point));
}

size_t Line::size () {
	lock_guard<mutex> lock(value_m);

	return points.size();
}

void Line::getBox (Point& begin, Point& end) {
	lock_guard<mutex> lock(value_m);

	auto dimensions = points[0].getDimensions();
	begin = Point(points[0]);
	end = Point(points[0]);

	for (auto p : points)
		for (size_t i = 0 ; i < dimensions ; i++) {
			auto v = p.getValue(i);
			auto b =  begin.getValue(i);
			auto e =  end.getValue(i);
			begin.setValue(i, v < b ? v : b);
			end.setValue(i, v > e ? v : e);
		}
}

void Line::for_each (std::function<void(Point)> foreachFunc) {
	lock_guard<mutex> lock(value_m);

	for (auto& point : points)
		foreachFunc(point);
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
