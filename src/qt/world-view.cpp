/**
 * \file world-view.cpp
 * \brief The Stibbons world view
 * \author Adrien Plazas
 * \version 0.2
 * \date 28/02/2015
 */

#include "world-view.h"

#include <QPainter>
#include <QPaintEvent>

namespace stibbons {

inline QPen pen(Color c) {
	auto qc = QColor();
	qc.setRgbF(c.r(), c.g(), c.b());
	return QPen(qc);
}

WorldView::WorldView(QWidget *parent) : QWidget(parent) {
	setMinimumSize(QSize(100, 100));
	connect(this, SIGNAL(changed()), this, SLOT(update()));
}

void WorldView::paintEvent(QPaintEvent *event) {
	auto rect = event->rect();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRect boundingRect;
	setMinimumHeight(boundingRect.height());

	if (getWorld())
		paint(painter, *getWorld(), rect.width() / 2, rect.height() / 2);
}

void WorldView::setWorld(World *world) {
	this->world = world;

	world->onChanged([this]() {
		emit changed();
	});
}

World *WorldView::getWorld() {
	return world;
}

void WorldView::paint(QPainter &p, World &world, int xt, int yt) {
	for (auto& line : world.getLines())
		paint(p, *line, xt, yt);

	for (auto& turtle : world.getTurtles())
		paint(p, *turtle, xt, yt);
}

void WorldView::paint(QPainter &p, Line &line, int xt, int yt) {
	size_t i = 0;
	auto points = new QPointF[line.size()] ();

	for (auto& point : line) {
		double x = point.getDimensions() < 1 ? 0 : point[0];
		double y = point.getDimensions() < 2 ? 0 : point[1];
		points[i].setX(x + xt);
		points[i].setY(y + yt);
		i++;
	}

	auto oldPen = p.pen();
	p.setPen(pen(line.getColor()));

	p.drawPolyline(points, line.size());

	p.setPen(oldPen);
}

void WorldView::paint(QPainter &p, Turtle &turtle, int xt, int yt) {
	auto oldPen = p.pen();
	p.setPen(pen(turtle.getColor()));

	auto triangle = getTriangle();
	paint(p, triangle, turtle[0] + xt, turtle[1] + yt, turtle.getAngle(), 5.0);

	p.setPen(oldPen);
}

void WorldView::paint(QPainter &p, QPolygon &polygon, double x, double y, double angle, double size) {
	auto transformations = QMatrix();
	transformations.rotate(angle);
	transformations.scale(size, size);

	auto trans_poly = transformations.map(polygon);
	trans_poly.translate(x, y);

	p.drawPolygon(trans_poly);
}

QPolygon WorldView::getTriangle() {
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
