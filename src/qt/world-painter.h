/**
 * \file world-painter.h
 * \brief The Stibbons world painter
 * \author Adrien Plazas
 * \version 1.0
 * \date 05/05/2015
 */

#pragma once

#include "../model/line.h"
#include "../model/turtle.h"
#include "../model/world.h"

#include <QPainter>

namespace stibbons {

	/**
	 * \class WorldPainter
	 * \brief The painter of the world in Qt application.
	 *
	 * \author Adrien Plazas
	 */
	class WorldPainter {
	public:
		/**
		 * Constructor
		 * \param world the world to paint
		 */
		WorldPainter(WorldPtr world);

		/**
		 * Reset the buffer which contains lines
		 */
		void resetLinesBuffer();

		/**
		 * Paint an object on the world view
		 * \param p object to paint
		 */
		void paint(QPainter &p);

		/**
		 * Paint an object on the world view
		 * \param p object to paint
		 * \param xt x translation
		 * \param yt y translation
		 */
		void paint(QPainter &p, int xt, int yt);

	private:
		void paint(QPainter &p, World &world, int xt, int yt);
		void paintWarped(QPainter &p, Line &line, int xt, int yt);
		void paint(QPainter &p, Line &line, int xt, int yt);
		void paint(QPainter &p, Turtle &turtle, int xt, int yt);

		void paint(QPainter &p, QPolygon &polygon, double x, double y, double angle, double size = 1.0);
		QPolygon getTriangle();

		vector<size_t> linesSizes;
		QImage linesBuffer;

		WorldPtr world;
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
