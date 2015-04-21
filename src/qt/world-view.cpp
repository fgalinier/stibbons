/**
 * \file world-view.cpp
 * \brief The Stibbons world view
 * \author Adrien Plazas
 * \version 0.4
 * \date 28/02/2015
 */

#include "world-view.h"

#include <QPainter>
#include <QPaintEvent>

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

WorldView::WorldView(QWidget *parent) :
	QWidget(parent),
	linesSizes(vector<size_t>()),
	linesBuffer(QPixmap()),
	world(nullptr) {
	linesBuffer.fill(Qt::transparent);
	connect(this, SIGNAL(changed()), this, SLOT(update()));
}

QSize WorldView::sizeHint() const {
	if (world) {
		auto worldSize = world->getWorldSize();
		auto zoneSize = world->getZoneSize();
		int w = worldSize.getValue(0) * zoneSize.getValue(0);
		int h = worldSize.getValue(1) * zoneSize.getValue(1);
		return QSize(w, h);
	}

	return QSize();
}

void WorldView::paintEvent(QPaintEvent *event) {
	auto rect = event->rect();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRect boundingRect;
	setMinimumHeight(boundingRect.height());

	if (getWorld())
		paint(painter, *getWorld(), 0, 0);
}

void WorldView::setWorld(WorldPtr world) {
	this->world = world;

	resize(sizeHint());
	updateGeometry();

	linesSizes = vector<size_t>();
	linesBuffer = QPixmap(sizeHint());
	linesBuffer.fill(Qt::transparent);

	world->onChanged([this]() {
		emit changed();
	});
}

WorldPtr WorldView::getWorld() {
	return world;
}

void WorldView::paint(QPainter &p, World &world, int xt, int yt) {
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
		paint(lp, line, xt, yt);
	p.drawPixmap(0, 0, linesBuffer);

	// Draw the turtles
	for (auto& turtle : world.getTurtles())
		paint(p, *turtle, xt, yt);
}

void WorldView::paint(QPainter &p, Line &line, int xt, int yt) {
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

	p.setPen(oldPen);
}

void WorldView::paint(QPainter &p, Turtle &turtle, int xt, int yt) {
	auto oldPen = p.pen();
	auto oldBrush = p.brush();
	p.setPen(pen(turtle.getColor()));
	p.setBrush(brush(turtle.getColor()));

	auto triangle = getTriangle();
	paint(p, triangle, turtle[0] + xt, turtle[1] + yt, turtle.getAngle(), 5.0);

	p.setPen(oldPen);
	p.setBrush(oldBrush);
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
