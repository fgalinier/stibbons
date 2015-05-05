/**
 * \file color.h
 * \brief A color
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.5
 * \date 14/03/2015
 */

#pragma once

#include "value.h"

#include <stdexcept>
#include <string>
#include <mutex>

#include <memory>

namespace stibbons {

/**
 * \class Color
 *
 * \brief A color.
 *
 * \author Adrien Plazas
 */
class Color : public GenericValue<Type::COLOR> {
	private:
		double red;
		double green;
		double blue;

		std::recursive_mutex value_m;

	public:
		/**
		 * Create a copy of a color
		 * @param other the other color
		 */
		Color (Color &other);

		/**
		 * Move a color
		 * @param other the other color
		 */
		Color (Color &&other);

		/**
		 * Copy of a color
		 * @param other the other color
		 */
		Color& operator= (Color& other);

		/**
		 * Move a color
		 * @param other the other color
		 */
		Color& operator= (Color&& other);

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

		virtual ~Color () = default;

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
		double r ();

		/**
		 * Return the value of green
		 * @return the value of green
		 */
		double g ();

		/**
		 * Return the value of blue
		 * @return the value of blue
		 */
		double b ();

		/**
		 * Add a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr add (ValuePtr other) throw(std::domain_error);

		/**
		 * Add a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ColorPtr add (ColorPtr other);

		/**
		 * Substract a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr substract (ValuePtr other) throw(std::domain_error);

		/**
		 * Substract a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ColorPtr substract (ColorPtr other);

		/**
		 * Multiply a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr multiply (ValuePtr other) throw(std::domain_error);

		/**
		 * Multiply a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ColorPtr multiply (ColorPtr other);

		/**
		 * Divide a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ValuePtr divide (ValuePtr other) throw(std::domain_error);

		/**
		 * Divide a value to another
		 * @param other the other value
		 * @return the resulting value
		 */
		virtual ColorPtr divide (ColorPtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a positive number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual int compare (ValuePtr other);

		/**
		 * Return whether the comparison value of two values
		 *
		 * Return a negative number if this value is lower than the other,
		 * return a negative number if this value is greater than the other,
		 * return 0 if they are equal.
		 *
		 * @param other the other value
		 * @return the comparison value of this and the other value
		 */
		virtual int compare (ColorPtr other);

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual std::string toString ();
};

typedef std::shared_ptr<Color> ColorPtr;

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
