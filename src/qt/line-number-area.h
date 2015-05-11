#pragma once

#include <QPlainTextEdit>
#include <QWidget>
#include <QSize>
#include "stibbons-editor.h"

class LineNumberArea : public QWidget {
 public:
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
