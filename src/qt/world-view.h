/**
 * \file world-view.h
 * \brief The Stibbons world view
 * \author Adrien Plazas
 * \version 0.5
 * \date 28/02/2015
 */

#pragma once

#include <QWidget>

#include "world-painter.h"

#include "../model/line.h"
#include "../model/turtle.h"
#include "../model/world.h"

namespace stibbons {

class WorldView : public QWidget {
	Q_OBJECT

	public:
		WorldView(QWidget *parent = nullptr);

		void setWorld(WorldPtr world);
		WorldPtr getWorld();

		virtual QSize sizeHint() const;

	protected:
		virtual void paintEvent(QPaintEvent *event);

	signals:
		void changed();

	private:
		WorldPtr world;
		WorldPainter worldPainter;
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
