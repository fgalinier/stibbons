#pragma once

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QWidget>
#include <QPainter>
#include <QSize>

class StibbonsEditor : public QPlainTextEdit {
    Q_OBJECT

 public:
    StibbonsEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int areaWidth() const;

 protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

	private slots:
		void updateLineNumberArea(const QRect &, int);
 
 private:
		QWidget *lineNumberArea;
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
