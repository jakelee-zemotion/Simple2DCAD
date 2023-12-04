#include "Viewport.h"
#include "Line.h"
#include "Face.h"

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

Viewport::~Viewport()
{
    for (const auto& object : mDrawObjects)
    {
        delete object;
    }
}

const QVector<Shape*>& Viewport::GetDrawObjects() const
{
    return mDrawObjects;
}

void Viewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen); 

    QBrush brush(Qt::red);
    painter.setBrush(brush);

    // Draw objects
    for (const auto& object : mDrawObjects)
    {
        object->Paint(painter);
    }

    // Draw temporary points of the undetermined shape.
    painter.drawPolyline(mTempPoints.data(), mTempPoints.size());
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        qDebug() << "left";
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

        if (!mIsDrawing)
        {
            // Put two points to create a line on the first click.
            // Therefore, the second point is adjusted in MouseMoveEvent.
            mTempPoints = { polylinePoint, polylinePoint };
            mIsDrawing = true;

            // Enable movement tracking when the mouse is not pressed.
            setMouseTracking(true);
        }
        else
        {
            mTempPoints.push_back(polylinePoint);
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

            if (!mTempPoints.isEmpty())
                mTempPoints.back() = polylinePoint;
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
            if (!mTempPoints.isEmpty())
            {
                // Remove adjusting point.
                mTempPoints.pop_back();

                // Put the shape in DrawObjects if its size is not 1. 
                // It is unnecessary to store a point.
                if (mTempPoints.size() > 1)
                {
                    // Close testing
                    QPoint startPoint = mTempPoints.front();
                    QPoint endPoint = mTempPoints.back();
                    if (IsObjectClosed(startPoint, endPoint))
                    {
                        qDebug() << "closed";

                        // Remove endPoint because drawPolygon() automatically connects the startPoint and endPoint.
                        mTempPoints.pop_back();


                        mDrawObjects.push_back(new Face(mTempPoints));
                    }
                    else
                    {
                        mDrawObjects.push_back(new Line(mTempPoints));
                    }
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
