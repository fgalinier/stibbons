/**
 * \file line.h
 * \brief A colored polyline
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.5
 * \date 14/03/2015
 */

#pragma once

#include <vector>
#include <mutex>

#include "point.h"
#include "color.h"

using namespace std;

namespace stibbons {

/**
 * \class Line
 *
 * \brief A colored polyline.
 *
 * \author Adrien Plazas
 */
class Line {
	public:
		/**
		 * Create a line
		 * \param point the initial point
		 */
		Line(Point point);

		/**
		 * Create a copy of a line
		 * \param other the other line
		 * \param since the point to copy the line from
		 */
		Line (Line &other, size_t since = 0);

		/**
		 * Move a line
		 * \param other the other line
		 */
		Line (Line &&other);

		/**
		 * Copy of a line
		 * \param other the other line
		 */
		Line& operator= (Line& other);

		/**
		 * Move a line
		 * \param other the other line
		 */
		Line& operator= (Line&& other);

		/**
		 * Set the value for an axis
		 * \param axis the axis
		 * \param value the value
		 */
		void setColor (Color color);

		/**
		 * Get the value for an axis
		 * \return a reference to the value for an axis
		 */
		Color& getColor ();

		/**
		 * Get the value for an axis
		 * \return a constant reference to the value for an axis
		 */
		const Color& getColor () const;

		/**
		 * Add a point
		 * \param point the point to add
		 */
		void push_back (Point point);

		/**
		 * Get the number of points
		 * \return the number of points in the line
		 */
		size_t size ();

		/**
		 * Get the points of the box containing the line
		 * \param begin the first corner of the box
		 * \param end the last corner of the box
		 */
		void getBox (Point& begin, Point& end);

		/**
		 * Do something for a copy of each point
		 * \param foreachFunc the fonction to call for each point
		 */
		void for_each (std::function<void(Point)> foreachFunc);

	private:
		Color color;
		vector<Point> points;

		recursive_mutex value_m;
};

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
