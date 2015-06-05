/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file changeable.h
 * \brief The Changeable header class
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
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
