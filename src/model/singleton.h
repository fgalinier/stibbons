/**
 * \file singleton.h
 * \brief A class representing a singleton
 * \author Adrien Plazas
 * \version 1.0
 * \date 19/03/2015
 */

#pragma once

#include "value.h"

using namespace std;

namespace stibbons {

/**
 * class Singleton
 *
 *\brief A helper class to implementing a singleton.
 *
 *\author Adrien Plazas
 */
template<class T>
class Singleton {
	public:
		Singleton (const Singleton<T>&) = delete;
		Singleton& operator= (const Singleton<T>&) = delete;

		/**
		 * Get the instance of the type T
		 * \return a reference of the instance
		 */
		static shared_ptr<T> getInstance () {
			static shared_ptr<T> instance = shared_ptr<T>(new T());
			return instance;
		}

	protected:
		Singleton () = default;
		~Singleton () = default;
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
