#include "Viewport.h"
#include "Line.h"
#include "Face.h"
#include "Camera.h"

#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>

using namespace std;

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    mIsDrawing = false;
    mIsCtrlPressed = false;

    mClosedThreshold.minX = 20;
    mClosedThreshold.minY = 20;
    mClosedThreshold.maxX = 20;
    mClosedThreshold.maxY = 20;

    mCamera.reset(new Camera(mShapeObjects, mTempPoints, { this->width(), this->height() }));

    // Enable movement tracking when the mouse is not pressed.
    setMouseTracking(true);
}

Viewport::~Viewport()
{
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
    for (int i = 0; i < mShapeObjects.size(); i++)
    {
        mShapeObjects[i]->Paint(painter);
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
                // Put two points to create a line on the first click.
                // Therefore, the second point is adjusted in MouseMoveEvent.
                mTempPoints = { currMousePos, currMousePos };
                mIsDrawing = true;
            }
            else
            {
                mTempPoints.push_back(currMousePos);

                // Close testing
                QPoint startPoint = mTempPoints.front();
                QPoint endPoint = currMousePos;
                if (IsObjectClosed(startPoint, endPoint))
                {
                    qDebug() << "closed";

                    // Remove two endPoints because drawPolygon() automatically connects the startPoint and endPoint.
                    mTempPoints.pop_back();
                    mTempPoints.pop_back();
                    mShapeObjects.emplace_back(new Face(mTempPoints));

                    mIsDrawing = false;
                    mTempPoints.clear();
                }
            }

        }
        break;

        // Panning
        case Qt::MiddleButton:
        {
            mCamera->SetPrevMousePos(currMousePos);
        }
        break;
    }

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
                    mShapeObjects.emplace_back(new Line(mTempPoints));
                }
                
            }

            mIsDrawing = false;
            mTempPoints.clear();

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
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    int mouseDir = event->angleDelta().y();

    // Zooming
    if (mIsCtrlPressed)
        mCamera->Zoom(currMousePos, mouseDir);

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
