/**
 * \file nil.h
 * \brief A class to represent the null value
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.5
 * \date 14/03/2015
 */

#pragma once

#include "value.h"
#include "singleton.h"

namespace stibbons {

/**
 * class Nil
 *
 * \brief A class to represent the null value.
 *
 * \author Julia Bassoumi, Adrien Plazas
 */
class Nil : public GenericValue<Type::NIL>, public Singleton<Nil> {
	friend Singleton<Nil>;
	protected:
		Nil () = default;
	public:
		/**
		 * Return a string corresponding to the value
		 * \return a string corresponding to the value
		 */
		virtual std::string toString ();
};

typedef std::shared_ptr<Nil> NilPtr;

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
