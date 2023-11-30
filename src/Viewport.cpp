#include "Viewport.h"
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    mIsDrawing = false;
}

void Viewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen); 

    QBrush brush(Qt::red);
    painter.setBrush(brush);

    for (const auto& polyLine : mPolylineVector)
    {
        painter.drawPolygon(polyLine.data(), polyLine.size());
    }
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

    if (mIsDrawing)
    {
        mPolylineVector.back().push_back(polylinePoint);
    }
    else
    {
        // Put two points to create a line on the first click.
        // Therefore, the second point is adjusted in MouseMoveEvent.
        mPolylineVector.push_back({ polylinePoint, polylinePoint });
        mIsDrawing = true;
    }

    // Enable movement tracking when the mouse is not pressed.
    setMouseTracking(true);

    update(); 
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    QPoint polylinePoint = QWidget::mapFromGlobal(QCursor::pos());

    if (!mPolylineVector.isEmpty() && !mPolylineVector.back().isEmpty())
       mPolylineVector.back().back() = polylinePoint;

    update();
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    // Key_Enter is the Enter key on the numeric keypad.
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Escape)
    {
        // Remove adjusting point.
        if (!mPolylineVector.isEmpty() && !mPolylineVector.back().isEmpty())
            mPolylineVector.back().pop_back();

        mIsDrawing = false;
        setMouseTracking(false);

        update();
    }

}
