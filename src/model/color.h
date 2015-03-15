/**
 * \file color.h
 * \brief A color
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.1
 * \date 14/03/2015
 */

#pragma once

#include "value.h"

#include <stdexcept>
#include <string>

namespace stibbons {

/**
 * \class Color
 *
 * \brief A color.
 *
 * \author Adrien Plazas
 */
class Color : public Value {
	private:
		double red;
		double green;
		double blue;

	public:
		/**
		 * Create a color from its red, green and blue values.
		 * @param red the value of the red composant
		 * @param green the value of the green composant
		 * @param blue the value of the blue composant
		 */
		Color (double red = 0.0, double green = 0.0, double blue = 0.0);

		/**
		 * Creates a color from an HTML style color string.
		 * @param color a stirng like #FFF or #FFFFFF
		 */
		Color (std::string color) throw(std::domain_error);

		Type getType () const;

		/**
		 * Set the value of red
		 * @param red the new value of red
		 */
		void r (double red);

		/**
		 * Set the value of green
		 * @param green the new value of green
		 */
		void g (double green);

		/**
		 * Set the value of blue
		 * @param blue the new value of blue
		 */
		void b (double blue);

		/**
		 * Return the value of red
		 * @return the value of red
		 */
		double r () const;

		/**
		 * Return the value of green
		 * @return the value of green
		 */
		double g () const;

		/**
		 * Return the value of blue
		 * @return the value of blue
		 */
		double b () const;
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