/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file world-painter.cpp
 * \brief The Stibbons world painter
 * \author Adrien Plazas
 * \version 1.1
 * \date 05/05/2015
 */

#include "world-painter.h"

namespace stibbons {

inline QColor color(Color c) {
	auto qc = QColor();
	qc.setRgbF(c.r(), c.g(), c.b());
	return qc;
}

inline QPen pen(Color c) {
	return QPen(color(c));
}

inline QBrush brush(Color c) {
	return QBrush(color(c));
}

WorldPainter::WorldPainter(WorldPtr world) :
	linesSizes(vector<size_t>()),
	linesBuffer(QImage()),
	world(world) {
	resetLinesBuffer();
}

void WorldPainter::resetLinesBuffer() {
	linesSizes = vector<size_t>();
	auto ws = world ? world->getSize() : Size();
	linesBuffer = QImage(ws.getValue(0), ws.getValue(1), QImage::Format_ARGB32);
	linesBuffer.fill(Qt::transparent);
}

void WorldPainter::paint(QPainter &p) {
	if (world)
		paint (p, *world, 0, 0);
}

void WorldPainter::paint(QPainter &p, int xt, int yt) {
	if (world)
		paint (p, *world, xt, yt);
}

void WorldPainter::paint(QPainter &p, World &world, int xt, int yt) {
	if (world.getDimensions() != 2)
		return;

	auto size = world.getZoneSize();
	int w = size.getValue(0);
	int h = size.getValue(1);

	// Draw the zones
	auto i = Size(world.getDimensions());
	for (i.setValue(0, 0) ;
	     i.getValue(0) < world.getWorldSize().getValue(0) ;
	     i.setValue(0, i.getValue(0) + 1))
	for (i.setValue(1, 0) ;
	     i.getValue(1) < world.getWorldSize().getValue(1) ;
	     i.setValue(1, i.getValue(1) + 1)) {
		int x = (int) i.getValue(0) * w + xt;
		int y = (int) i.getValue(1) * h + yt;

		p.fillRect(x, y, w, h, color(world.getZone(i)->getColor()));
	}

	// Draw the lines
	QPainter lp(&linesBuffer);
	for (auto& line : world.getLinesSince(linesSizes))
		paintWarped(lp, line, xt, yt);
	p.drawImage(0, 0, linesBuffer);

	// Draw the turtles
	for (auto& turtle : world.getTurtles())
		paint(p, *turtle, xt, yt);
}

void WorldPainter::paintWarped(QPainter &p, Line &line, int xt, int yt) {
	if (line.size() == 0)
		return;

	Point begin, end;
	line.getBox(begin, end);

	auto ws = world->getSize();
	long w = ws.getValue(0);
	long h = ws.getValue(1);

	auto borderTypes = world->getBorderTypes();

	long x = borderTypes[0] == BorderType::WRAP ? w * (1 - ((long) floor(begin.getValue(0)) / w)) :
	                   w;

	do {
		long y = borderTypes[1] == BorderType::WRAP ? h * (1 - ((long) floor(begin.getValue(1)) / h)) :
		                   h;
		do {
			paint(p, line, xt + x-w, yt + y-h);
			y -= h;
		} while (end.getValue(1)+y > h && borderTypes[1] == BorderType::WRAP);
		x -= w;
	} while (end.getValue(0)+x > w && borderTypes[0] == BorderType::WRAP);
}

void WorldPainter::paint(QPainter &p, Line &line, int xt, int yt) {
	Line l(line);

	size_t i = 0;
	size_t *ip = &i;
	auto points = new QPointF[l.size()] ();

	l.for_each ([points, ip, xt, yt](Point p){
		if (p.getDimensions() >= 2) {
			points[*ip].setX(p[0] + xt);
			points[*ip].setY(p[1] + yt);
			(*ip)++;
		}
	});

	auto oldPen = p.pen();
	p.setPen(pen(l.getColor()));

	p.drawPolyline(points, l.size());

	delete[] points;

	p.setPen(oldPen);
}

void WorldPainter::paint(QPainter &p, Turtle &turtle, int xt, int yt) {
	auto oldPen = p.pen();
	auto oldBrush = p.brush();
	p.setPen(pen(turtle.getColor()));
	p.setBrush(brush(turtle.getColor()));

	auto triangle = getTriangle();
	auto position = turtle.getPosition();
	paint(p, triangle, position.getValue(0) + xt, position.getValue(1) + yt, turtle.getAngle(), 5.0);

	p.setPen(oldPen);
	p.setBrush(oldBrush);
}

void WorldPainter::paint(QPainter &p, QPolygon &polygon, double x, double y, double angle, double size) {
	auto transformations = QMatrix();
	transformations.rotate(angle);
	transformations.scale(size, size);

	auto trans_poly = transformations.map(polygon);
	trans_poly.translate(x, y);

	p.drawPolygon(trans_poly);
}

QPolygon WorldPainter::getTriangle() {
	return QPolygon(QVector<QPoint> {
		QPoint(-1, -1),
		QPoint(-1,  1),
		QPoint( 1,  0)
	});
}

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
