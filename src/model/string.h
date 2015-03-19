/**
 * \file string.h
 * \brief A class representing a string
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.2
 * \date 14/03/2015
 */

#pragma once

#include "value.h"
#include "simple-value.h"

#include <string>

namespace stibbons {

/**
 * \class String
 *
 * \brief A class representing a string.
 *
 * \author Julia Bassoumi, Adrien Plazas
 */
class String : public Value, public SimpleValue<std::string> {
	public:
		using SimpleValue<std::string>::SimpleValue;

		Type getType() const;
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
