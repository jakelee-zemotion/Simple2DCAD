#include "scViewport.h"

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
    mScene = make_shared<scScene>(this->geometry());

    mIsCtrlPressed = false;

    // Enable movement tracking when the mouse is not pressed.
    setMouseTracking(true);
}

scViewport::~scViewport()
{
}

void scViewport::AddState(const string& name)
{
    shared_ptr<scState> state;

    if (name == "Draw")
        state = make_shared<scDrawLineState>(mScene);
    else if (name == "SelectVertex")
        state = make_shared<scSelectState>(mScene, SELECT::VERTEX);
    else if (name == "SelectLine")
        state = make_shared<scSelectState>(mScene, SELECT::LINE);


    mStateMachine.AddState(name, state);
}

void scViewport::TransitState(const string& name)
{
    mStateMachine.Transition(name);
}

void scViewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    
    // Draw objects
    mScene->Render(painter);
}

void scViewport::mousePressEvent(QMouseEvent* event)
{
    QPointF currMousePos = QWidget::mapFromGlobal(QCursor::pos());

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
            //mCamera->SetPrevMousePos(currMousePos);
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
    QPointF currMousePos = QWidget::mapFromGlobal(QCursor::pos());
    
    // The last point tracks the mouse in drawing mode
    mStateMachine.GetCurrentState()->MouseMoveEvent(currMousePos);

    // Panning
    switch (event->buttons())
    {
        case Qt::MiddleButton:
        {
            //mCamera->Pan(currMousePos);
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
        mCamera.Zoom(currMousePos, mouseDir);

    update();
}


