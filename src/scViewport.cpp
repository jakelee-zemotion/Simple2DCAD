#include "scViewport.h"

// system
#include <memory>

// qt
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QKeyEvent>

// Simple2DCAD
#include "scScene.h"
#include "scCoordinateHelper.h"
#include "scGrid.h"

using namespace std;

scViewport::scViewport(QWidget* parent)
	:QWidget(parent), mViewportWidth(700), mViewportHeight(500)
{
    setFixedSize(mViewportWidth, mViewportHeight);
    setStyleSheet("background-color:white;");
    setMouseTracking(true); // Enable movement tracking when the mouse is not pressed.

    mCoordinateHelper = make_shared<scCoordinateHelper>(mCamera, this->geometry());
    mGrid = make_shared<scGrid>(mCoordinateHelper, mCamera, this->geometry());
    mScene = make_shared<scScene>(mCoordinateHelper, mGrid);

    mIsCtrlPressed = false;
}

void scViewport::AddState(const string& name)
{
    mStateMachine.AddState(name, mScene, mCoordinateHelper);
}

void scViewport::TransitState(const string& name)
{
    mStateMachine.EndState();
    mStateMachine.Transition(name);

    // Update for EndState()
    update();
}

void scViewport::ResetScene()
{
    mStateMachine.EndState();

    mScene->ClearData();
    update();
}

void scViewport::SaveScene(const string& fileName)
{
    mStateMachine.EndState();

    mScene->SaveData(fileName);
    update();
}

void scViewport::OpenScene(const string& fileName)
{
    mStateMachine.EndState();

    mScene->LoadData(fileName);
    update();
}

void scViewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Draw objects
    mScene->Render(painter);
    mStateMachine.Paint(painter);
}

void scViewport::mousePressEvent(QMouseEvent* event)
{
    const QPointF currMousePosQPointF = QWidget::mapFromGlobal(QCursor::pos());
    const scVector2D currMousePos = { currMousePosQPointF.x(), currMousePosQPointF .y() };

    switch (event->buttons())
    {
        case Qt::LeftButton:
        {
            mStateMachine.GetCurrentState()->MousePressEvent(currMousePos);
        }
        break;

        // Pan
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
    mStateMachine.GetCurrentState()->MouseReleaseEvent();

    update();
}

void scViewport::mouseMoveEvent(QMouseEvent* event)
{
    const QPointF currMousePosQPointF = QWidget::mapFromGlobal(QCursor::pos());
    const scVector2D currMousePos = { currMousePosQPointF.x(), currMousePosQPointF.y() };
    
    // The last point tracks the mouse in drawing mode
    mStateMachine.GetCurrentState()->MouseMoveEvent(currMousePos);

    // Pan
    switch (event->buttons())
    {
        case Qt::MiddleButton:
        {
            mGrid->PanEvent();
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
    const QPointF currMousePosQPointF = QWidget::mapFromGlobal(QCursor::pos());
    const scVector2D currMousePos = { currMousePosQPointF.x(), currMousePosQPointF.y() };

    int mouseDir = event->angleDelta().y();

    // Zoom
    if (mIsCtrlPressed)
    {
        mCamera.ZoomInOut(currMousePos, mouseDir);
        mGrid->ZoomEvent(mouseDir);
    }

    update();
}


