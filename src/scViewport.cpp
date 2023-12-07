#include "scViewport.h"
#include "scCamera.h"
#include "scDrawLineState.h"
#include "scSelectState.h"

#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>
#include <memory>

using namespace std;

scViewport::scViewport(QWidget* parent)
	:QWidget(parent)
{
    mIsCtrlPressed = false;

    mCamera = make_unique<scCamera>(mShapeObjects, QPoint(this->width(), this->height()));

    mStateMachine.AddState("Draw", make_shared<scDrawLineState>(mShapeObjects));
    mStateMachine.AddState("Select", make_shared<scSelectState>(mShapeObjects));

    // Enable movement tracking when the mouse is not pressed.
    setMouseTracking(true);
}

scViewport::~scViewport()
{
}

void scViewport::TransitState(std::string name)
{
    mStateMachine.Transition(name);
}

void scViewport::paintEvent(QPaintEvent* event)
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

void scViewport::mousePressEvent(QMouseEvent* event)
{
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());

    switch (event->buttons())
    {
        case Qt::LeftButton:
        {
            mStateMachine.GetCurrentState()->MousePressEvent(currMousePos);
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

void scViewport::mouseReleaseEvent(QMouseEvent* event)
{
    //qDebug() << event->buttons();

    mStateMachine.GetCurrentState()->MouseReleaseEvent();

    update();
}

void scViewport::mouseMoveEvent(QMouseEvent* event)
{
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    
    // The last point tracks the mouse in drawing mode
    mStateMachine.GetCurrentState()->MouseMoveEvent(currMousePos);

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

void scViewport::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        // Key_Enter is the Enter key on the numeric keypad.
        case Qt::Key_Return:
        case Qt::Key_Escape:
        {
            mStateMachine.GetCurrentState()->KeyPressEvent();
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

void scViewport::keyReleaseEvent(QKeyEvent* event)
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

void scViewport::wheelEvent(QWheelEvent* event)
{
    QPoint currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    int mouseDir = event->angleDelta().y();

    // Zooming
    if (mIsCtrlPressed)
        mCamera->Zoom(currMousePos, mouseDir);

    update();
}

