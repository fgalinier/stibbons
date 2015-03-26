/**
 * \file world-view.h
 * \brief The Stibbons world view
 * \author Adrien Plazas
 * \version 0.2
 * \date 28/02/2015
 */

#pragma once

#include <QWidget>

#include "../model/line.h"
#include "../model/turtle.h"
#include "../model/world.h"

namespace stibbons {

class WorldView : public QWidget {
	Q_OBJECT

	public:
		WorldView(QWidget *parent = nullptr);

		void setWorld(World *world);
		World *getWorld();

	protected:
		virtual void paintEvent(QPaintEvent *event);

	signals:
		void changed();

	private:
		void paint(QPainter &p, World &world);
		void paint(QPainter &p, Line &line);
		void paint(QPainter &p, Turtle &turtle);

		void paint(QPainter &p, QPolygon &polygon, double x, double y, double angle, double size = 1.0);
		QPolygon getTriangle();

		World *world;
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
