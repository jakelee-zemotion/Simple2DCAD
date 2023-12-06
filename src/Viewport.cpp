#include "Viewport.h"
#include "Camera.h"
#include "DrawLineState.h"
#include "SelectState.h"

#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>
#include <memory>

using namespace std;

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
    mIsCtrlPressed = false;

    mCamera = make_unique<Camera>(mShapeObjects, QPoint(this->width(), this->height()));

    mStateMachine.AddState("Draw", make_shared<DrawLineState>(mShapeObjects));
    mStateMachine.AddState("Select", make_shared<SelectState>(mShapeObjects));

    // Enable movement tracking when the mouse is not pressed.
    setMouseTracking(true);
}

Viewport::~Viewport()
{
}

void Viewport::TransitState(std::string name)
{
    mStateMachine.Transition(name);
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

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << event->buttons();

    mStateMachine.GetCurrentState()->MouseReleaseEvent();

    update();
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
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

void Viewport::keyPressEvent(QKeyEvent* event)
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


