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
 * \file line-number-area.h
 * \brief The LineNumberArea class header
 * \author Florian Galinier
 * \version 1.1
 * \date 05/05/2015
 */
#pragma once

#include <QPlainTextEdit>
#include <QWidget>
#include <QSize>
#include "stibbons-editor.h"

/**
 * \class LineNumberArea
 * \brief Widget that contain the line number area
 *
 * \author Florian Galinier
 */
class LineNumberArea : public QWidget {
 public:
	/**
	 * Constructor
	 * \param editor the stibbons editor
	 */
    LineNumberArea(StibbonsEditor *editor) : QWidget(editor), editor(editor) {}

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(editor->areaWidth(), 0);
    }

 protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        editor->lineNumberAreaPaintEvent(event);
    }

 private:
    StibbonsEditor *editor;
};


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
