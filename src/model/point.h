/**
 * \file point.h
 * \brief A point with a parametrable number of dimensions
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.3
 * \date 14/03/2015
 */

#pragma once

#include <stdexcept>
#include <mutex>

using namespace std;

namespace stibbons {

/**
 * \class Point
 *
 * \brief A point with a parametrable number of dimensions.
 *
 * \author Adrien Plazas
 */
class Point {
	public:
		/**
		 * Create a point of a given dimension
		 * @param dimensions the number of dimensions of the point
		 */
		Point (unsigned dimensions = 2);

		/**
		 * Create a copy of a point
		 * @param other the other point
		 */
		Point (Point &other);

		/**
		 * Move a point
		 * @param other the other point
		 */
		Point (Point &&other);

		/**
		 * Copy of a point
		 * @param other the other point
		 */
		Point& operator= (Point& other);

		/**
		 * Move a point
		 * @param other the other point
		 */
		Point& operator= (Point&& other);

		/**
		 * Set the value for an axis
		 * @param axis the axis
		 * @param value the value
		 */
		void setValue (unsigned axis, double value) throw(out_of_range);

		/**
		 * Get the value for an axis
		 * @return the value for an axis
		 */
		double getValue (unsigned axis) throw(out_of_range);

		/**
		 * Get the number of dimensions
		 * @return the number of dimensions
		 */
		unsigned getDimensions () const;

		/**
		 * Get the distance to another point
		 * @param other the other point
		 * @return the distance to the other point
		 */
		double getDistanceTo (Point& other);

		/**
		 * Get the angle with the horizontal axis to another point in radian
		 * @param other the other point
		 * @return the angle with the horizontal axis to another point
		 */
		double getAngleTo (Point& other);

		/**
		 * Get the value for an axis
		 * @return the value for an axis
		 */
		double operator[] (unsigned axis) throw(out_of_range);

	private:
		unsigned dimensions;
		double* axes;

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
