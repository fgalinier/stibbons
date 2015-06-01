/**
 * \file world-view.h
 * \brief The Stibbons world view
 * \author Adrien Plazas
 * \version 1.1
 * \date 28/02/2015
 */

#pragma once

#include <QWidget>

#include "world-painter.h"

#include "../model/line.h"
#include "../model/turtle.h"
#include "../model/world.h"

namespace stibbons {

	/**
	 * \class WorldView
	 * \brief The view of the world in Qt application.
	 *
	 * \author Adrien Plazas
	 */
	class WorldView : public QWidget {
		Q_OBJECT

	public:
		
		/**
		 * Constructor
		 * \param parent the parent widget
		 */
		WorldView(QWidget *parent = nullptr);

		/**
		 * Set the current world with the param
		 * \param world the new world
		 */
		void setWorld(WorldPtr world);

		/**
		 * Get the current world
		 * \return the current world
		 */
		WorldPtr getWorld();

		virtual QSize sizeHint() const;

	protected:
		virtual void paintEvent(QPaintEvent *event);

	signals:
		/**
		 * Method to call when the world changed
		 */
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
