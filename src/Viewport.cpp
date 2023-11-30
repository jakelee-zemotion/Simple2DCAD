#include "Viewport.h"
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    mIsDrawing = false;

    mClosedThreshold.minX = 20;
    mClosedThreshold.minY = 20;
    mClosedThreshold.maxX = 20;
    mClosedThreshold.maxY = 20;
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
        painter.drawPolyline(polyLine.data(), polyLine.size());
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

        // Enable movement tracking when the mouse is not pressed.
        setMouseTracking(true);
    }


    update(); 
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    if (mIsDrawing)
    {
        QPoint polylinePoint = QWidget::mapFromGlobal(QCursor::pos());

        if (!mPolylineVector.isEmpty() && !mPolylineVector.back().isEmpty())
            mPolylineVector.back().back() = polylinePoint;
    }

    update();
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    // Key_Enter is the Enter key on the numeric keypad.
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Escape)
    {
        if (!mPolylineVector.isEmpty() && !mPolylineVector.back().isEmpty())
        {
            // Remove adjusting point.
            mPolylineVector.back().pop_back();

            // Remove if size is 1. (it is unnecessary to store a point)
            if (mPolylineVector.back().size() == 1)
                mPolylineVector.pop_back();

            // Close testing
            QPoint startPoint = mPolylineVector.back().front();
            QPoint endPoint = mPolylineVector.back().back();
            if (IsObjectClosed(startPoint, endPoint))
            {
                qDebug() << "closed";
            }
        }

        mIsDrawing = false;
        setMouseTracking(false);

        update();
    }

}

bool Viewport::IsObjectClosed(QPoint start, QPoint end) const
{
    if (start.x() - mClosedThreshold.minX < end.x()
        && start.x() + mClosedThreshold.maxX > end.x()

        && start.y() - mClosedThreshold.minY < end.y()
        && start.y() + mClosedThreshold.maxY > end.y())
    {
        return true;
    }

    return false;
}
