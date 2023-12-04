#include "Viewport.h"
#include "Line.h"
#include "Face.h"
#include "Shape.h"
#include "Camera.h"

#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    mIsDrawing = false;
    mIsCtrlPressed = false;

    mClosedThreshold.minX = 20;
    mClosedThreshold.minY = 20;
    mClosedThreshold.maxX = 20;
    mClosedThreshold.maxY = 20;

    mCamera = new Camera(mDrawObjects, mTempPoints, { this->width(), this->height() });

    // Enable movement tracking when the mouse is not pressed.
    setMouseTracking(true);
}

Viewport::~Viewport()
{
    for (const auto& object : mDrawObjects)
    {
        delete object;
    }
}

void Viewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPen pen(Qt:: black);
    pen.setWidth(2);
    painter.setPen(pen); 

    QBrush brush(Qt::gray);
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
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());

    switch (event->buttons())
    {
        case Qt::LeftButton:
        {

            if (!mIsDrawing)
            {
                // Store mouse point as polyline point.
                // Create a line on the first click.
                mTempPoints = { currMousePos };
                mIsDrawing = true;
            }

            mTempPoints.push_back(currMousePos);
        }
        break;

        case Qt::MiddleButton:
        {
            mCamera->SetPrevMousePos(currMousePos);
        }
        break;
    }

    // Panning

    // Call for Keyboard Events.
    setFocus();
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << event->buttons();

    update();
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    
    // The last point tracks the mouse in drawing mode
    if (mIsDrawing && !mTempPoints.isEmpty())
    {
        mTempPoints.back() = currMousePos;
    }

    // Panning
    switch (event->buttons())
    {
        case Qt::MiddleButton:
        {
            mCamera->Pan(currMousePos);
        }
        break;
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

                    mTempPoints.clear();
                }
                
            }

            mIsDrawing = false;

            update();
        }
        break;

        case Qt::Key_Control: 
        {
            mIsCtrlPressed = true;
        }
        break;
    }

}

void Viewport::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Control:
        {
            mIsCtrlPressed = false;
        }
        break;
    }
}

void Viewport::wheelEvent(QWheelEvent* event)
{
    // Zooming
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    int mouseDir = event->angleDelta().y();

    mCamera->Zoom(mIsCtrlPressed, currMousePos, mouseDir);

    update();
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
