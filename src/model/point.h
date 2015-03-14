/**
 * \file point.h
 * \brief A point with a parametrable number of dimensions
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.1
 * \date 14/03/2015
 */

#pragma once

#include <stdexcept>

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
		 * Set the value for an axis
		 * @param axis the axis
		 * @param value the value
		 */
		void setValue (unsigned axis, double value) throw(out_of_range);

		/**
		 * Get the value for an axis
		 * @return a reference to the value for an axis
		 */
		double& getValue (unsigned axis) throw(out_of_range);

		/**
		 * Get the value for an axis
		 * @return a constant reference to the value for an axis
		 */
		const double& getValue (unsigned axis) const throw(out_of_range);

		/**
		 * Get the number of dimensions
		 * @return the number of dimensions
		 */
		unsigned getDimensions () const;

		/**
		 * Get the value for an axis
		 * @return a reference to the value for an axis
		 */
		double& operator[] (unsigned axis) throw(out_of_range);

		/**
		 * Get the value for an axis
		 * @return a constant reference to the value for an axis
		 */
		const double& operator[] (unsigned axis) const throw(out_of_range);

	private:
		unsigned dimensions;
		double* axes;
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
