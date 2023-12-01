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

    for (const auto& object : mDrawObjects)
    {
        QVector<QPoint> points = object.points;

        if (object.isPolygon)
            painter.drawPolygon(points.data(), points.size());
        else
            painter.drawPolyline(points.data(), points.size());
    }
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        qDebug() << "left";
        // ... handle left click here
    }

    // Call for Keyboard Events.
    setFocus();
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << event->buttons();
    //if (event->buttons() == Qt::LeftButton)
    {
        // Store mouse point as polyline point.
        QPoint polylinePoint = QWidget::mapFromGlobal(QCursor::pos());

        if (mIsDrawing)
        {
            QVector<QPoint>& points = mDrawObjects.back().points;
            points.push_back(polylinePoint);
        }
        else
        {
            // Put two points to create a line on the first click.
            // Therefore, the second point is adjusted in MouseMoveEvent.
            mDrawObjects.push_back({ { polylinePoint, polylinePoint }, false });
            mIsDrawing = true;

            // Enable movement tracking when the mouse is not pressed.
            setMouseTracking(true);
        }


    }

    update();
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    //if (event->buttons() == Qt::LeftButton)
    {
        if (mIsDrawing)
        {
            QPoint polylinePoint = QWidget::mapFromGlobal(QCursor::pos());

            if (!mDrawObjects.isEmpty() && !mDrawObjects.back().points.isEmpty())
                mDrawObjects.back().points.back() = polylinePoint;
        }
    }

    update();
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        // Key_Enter is the Enter key on the numeric keypad.
        case Qt::Key_Return:
        case Qt::Key_Escape:
        {
            if (!mDrawObjects.isEmpty() && !mDrawObjects.back().points.isEmpty())
            {
                // Remove adjusting point.
                mDrawObjects.back().points.pop_back();

                // Remove if size is 1. (it is unnecessary to store a point)
                if (mDrawObjects.back().points.size() == 1)
                    mDrawObjects.pop_back();

                // Close testing
                QPoint startPoint = mDrawObjects.back().points.front();
                QPoint endPoint = mDrawObjects.back().points.back();
                if (IsObjectClosed(startPoint, endPoint))
                {
                    qDebug() << "closed";
                    mDrawObjects.back().isPolygon = true;

                    // Remove endPoint because drawPolygon() automatically connects the startPoint and endPoint.
                    mDrawObjects.back().points.pop_back();
                }
            }

            mIsDrawing = false;
            setMouseTracking(false);

            update();
        }
        break;
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

bool Viewport::IsDrawObjectsEmpty() const
{
    return false;
}
