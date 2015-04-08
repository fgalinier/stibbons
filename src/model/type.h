/**
 * \file value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 0.3
 * \date 08/04/2015
 */

#pragma once

#include <string>

namespace stibbons {

/**
 * \class Type
 *
 * \brief The available value types.
 *
 * \author Julia Bassoumi
 */
enum class Type {
	NIL,
	NUMBER,
	BOOLEAN,
	STRING,
	COLOR,
	TABLE,
	FUNCTION,
	TURTLE,
	ZONE,
	WORLD
};

std::string toString(Type& type);
std::string toString(Type&& type);

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
