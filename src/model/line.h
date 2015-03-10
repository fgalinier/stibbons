/**
 * \file line.h
 * \brief A colored polyline
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.1
 * \date 14/03/2015
 */

#pragma once

#include <vector>

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
class Line : public vector<Point> {
	public:
		/**
		 * Set the value for an axis
		 * @param axis the axis
		 * @param value the value
		 */
		void setColor (Color color);

		/**
		 * Get the value for an axis
		 * @return a reference to the value for an axis
		 */
		Color& getColor ();

		/**
		 * Get the value for an axis
		 * @return a constant reference to the value for an axis
		 */
		const Color& getColor () const;

	private:
		Color color;
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
