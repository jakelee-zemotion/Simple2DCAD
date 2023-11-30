#include "Viewport.h"
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    isDrawing = false;
}

void Viewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen);

    for (const auto& polyLine : mPolylineVector)
    {
        painter.drawPolyline(polyLine.data(), polyLine.size());
    }

    QVector<QPointF> points = {
        QPointF(10.0, 80.0),
        QPointF(20.0, 10.0),
        QPointF(80.0, 30.0),
    };

    painter.drawPolyline(points.data(), points.size());
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    // Call for Keyboard Events.
    setFocus();
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    // Store mouse point as polyline point.
    QPoint polylinePoint = QWidget::mapFromGlobal(QCursor::pos());

    if (isDrawing)
    {
        mPolylineVector.back().push_back(polylinePoint);
    }
    else
    {
        // Put two points to create a line on the first click.
        // Therefore, the second point is adjusted in MouseMoveEvent.
        mPolylineVector.push_back({ polylinePoint, polylinePoint });
        isDrawing = true;
    }

    update();

    setMouseTracking(true);
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    QPoint polylinePoint = QWidget::mapFromGlobal(QCursor::pos());

    if (!mPolylineVector.isEmpty() || !mPolylineVector.back().isEmpty())
       mPolylineVector.back().back() = polylinePoint;

    update();
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    // Key_Enter is the Enter key on the numeric keypad.
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Escape)
    {
        // Remove adjusting point.
        if (!mPolylineVector.isEmpty() || !mPolylineVector.back().isEmpty())
            mPolylineVector.back().pop_back();

        isDrawing = false;
        setMouseTracking(false);

        update();
    }

}
