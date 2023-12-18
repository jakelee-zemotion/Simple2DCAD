#include "scViewport.h"

#include "scDrawLineState.h"
#include "scSelectState.h"
#include "scSelectVertexState.h"
#include "scSelectLineState.h"
#include "scSelectFaceState.h"

#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>
#include <memory>

using namespace std;

scViewport::scViewport(QWidget* parent)
	:QWidget(parent)
{
    mCoordinate = make_shared<scCoordinate>(mCamera, this->geometry());
    mScene = make_shared<scScene>(mCoordinate);

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
    else if (name == "SelectAll")
        state = make_shared<scSelectState>(mScene, SHAPE_TYPE::VERTEX | SHAPE_TYPE::LINE | SHAPE_TYPE::FACE);
    else if (name == "SelectVertex")
        state = make_shared<scSelectState>(mScene, SHAPE_TYPE::VERTEX);
    else if (name == "SelectLine")
        state = make_shared<scSelectState>(mScene, SHAPE_TYPE::LINE);
    else if (name == "SelectFace")
        state = make_shared<scSelectState>(mScene, SHAPE_TYPE::FACE);


    mStateMachine.AddState(name, state);
}

void scViewport::TransitState(const string& name)
{
    mStateMachine.Transition(name);

    // Update for EndState()
    update();
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
            mCamera.SetPrevMousePos(currMousePos);
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
            mCamera.AddPanXY(currMousePos);
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
        case Qt::Key_Delete:
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
        {
            mStateMachine.GetCurrentState()->KeyPressEvent(event);
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
       // mCamera.Zoom(currMousePos, mouseDir);

    update();
}


