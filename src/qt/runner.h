/**
 * \file runner.h
 * \brief Run Stibbons code in its own thread
 * \author Adrien Plazas
 * \version 0.4
 * \date 25/03/2015
 */

#pragma once

#include <QThread>

#include <string>

#include "../interpreter/world-interpreter.h"

namespace stibbons {

class Runner : public QThread {
	public:
		Runner(std::string& program);
		~Runner();
		WorldPtr getWorld();
		void run();

	private:
		WorldInterpreter* interpreter;
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
