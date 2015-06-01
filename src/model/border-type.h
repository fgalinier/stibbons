/**
 * \file border-type.h
 * \brief The BorderType header class
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
 * \date 14/03/2015
 */
#pragma once

namespace stibbons {

/**
 * \class BorderType
 *
 * \brief The type of borders.
 *
 * \author Adrien Plazas
 */
enum class BorderType {
	NONE,
	BOUNCE,
	WRAP
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
