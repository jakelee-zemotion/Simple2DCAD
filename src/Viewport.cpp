#include "Viewport.h"
#include <QPainter>
#include <QtWidgets/QApplication>

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    mStartPoint = { 0, 0 };
    mEndPoint = { 110, 0 };
}

void Viewport::paintEvent(QPaintEvent* event)
{
    QPainter MyPainter(this);
    QPen LinePen(Qt::green);
    LinePen.setWidth(2);

    MyPainter.setPen(LinePen);
    MyPainter.drawLine(mStartPoint, mEndPoint);
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    mStartPoint = QWidget::mapFromGlobal(QCursor::pos());
    mEndPoint = mStartPoint;
    update();
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    mEndPoint = QWidget::mapFromGlobal(QCursor::pos());
    update();
}
