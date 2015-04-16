/**
 * \file string.h
 * \brief A class representing a string
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.3
 * \date 14/03/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"

#include <string>

#include <memory>

namespace stibbons {

/**
 * \class String
 *
 * \brief A class representing a string.
 *
 * \author Julia Bassoumi, Adrien Plazas
 */
class String : public GenericValue<Type::STRING>, public SimpleValue<std::string> {
	public:
		using SimpleValue<std::string>::SimpleValue;
		virtual ~String () = default;

		virtual void reset ();

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();
};

typedef std::shared_ptr<String> StringPtr;

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
