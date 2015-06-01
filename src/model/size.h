/**
 * \file size.h
 * \brief A size with a parametrable number of dimensions
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
 * \date 08/04/2015
 */

#pragma once

#include <stdexcept>
#include <mutex>

using namespace std;

namespace stibbons {

/**
 * \class Size
 *
 * \brief A size with a parametrable number of dimensions.
 *
 * \author Adrien Plazas
 */
class Size {
	public:
		/**
		 * Create a size of a given dimension
		 * \param dimensions the number of dimensions of the size
		 */
		Size (unsigned dimensions = 2);

		/**
		 * Create a copy of a size
		 * \param other the other size
		 */
		Size (Size &other);

		/**
		 * Move a size
		 * \param other the other size
		 */
		Size (Size &&other);

		/**
		 * Copy of a size
		 * \param other the other size
		 */
		Size& operator= (Size& other);

		/**
		 * Move a size
		 * \param other the other size
		 */
		Size& operator= (Size&& other);

		/**
		 * Destroy a size
		 */
		virtual ~Size ();

		/**
		 * Set the value for an axis
		 * \param axis the axis
		 * \param value the value
		 */
		void setValue (unsigned axis, size_t value) throw(out_of_range);

		/**
		 * Get the value for an axis
		 * \return the value for an axis
		 */
		size_t getValue (unsigned axis) throw(out_of_range);

		/**
		 * Get the number of dimensions
		 * \return the number of dimensions
		 */
		unsigned getDimensions () const;

		/**
		 * Get the value for an axis
		 * \return the value for an axis
		 */
		size_t operator[] (unsigned axis) throw(out_of_range);

	private:
		unsigned dimensions;
		size_t* axes;

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
