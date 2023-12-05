#include "Viewport.h"
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

    mCamera.reset(new Camera(mShapeObjects, { this->width(), this->height() }));

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
    mShapeObjects.DrawShape(painter);
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
                mShapeObjects.CreateNewLine({ currMousePos, currMousePos });
                mIsDrawing = true;
            }
            else
            {
                mShapeObjects.AddPointInLastShape(currMousePos);

                // Close testing
                // If CloseTest is true (i.e. if polygon can be created), Drawing mode is stopped.
                mIsDrawing = !mShapeObjects.CloseTest(currMousePos);
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
    if (mIsDrawing)
    {
        mShapeObjects.SetLastPoint(currMousePos);
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
            mShapeObjects.CheckLastShape();
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
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    int mouseDir = event->angleDelta().y();

    // Zooming
    if (mIsCtrlPressed)
        mCamera->Zoom(currMousePos, mouseDir);

    update();
}


