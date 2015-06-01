/**
 * \file changeable.h
 * \brief The Changeable header class
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.0
 * \date 14/03/2015
 */

#pragma once

#include "color.h"

#include <functional>

namespace stibbons {

/**
 * \class Changeable
 *
 * \brief A class which can trigger a callback when its object has
 * changed.
 *
 * \author Adrien
 */
class Changeable {
	public:
		/**
		 * Create a changeable
		 */
		Changeable ();

		/**
		 * Set the callback function to trigger when the object has
		 * changed
		 *
		 * Only one callback function can be set at a time
		 *
		 * \param callback the callback function
		 */
		void onChanged (std::function<void()> callback);

		/**
		 * Signal that an object has changed
		 */
		void changed ();

	private:
		std::function<void()> callback;
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
