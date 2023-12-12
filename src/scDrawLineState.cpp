#include "scDrawLineState.h"

#include <QPointF>

using namespace std;

scDrawLineState::scDrawLineState(shared_ptr<scScene> scene)
    :scState(scene)
{
    mIsDrawing = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(QPointF& currMousePos)
{
    mScene->AddVertex(currMousePos, mIsDrawing);
    mIsDrawing = true;
}

void scDrawLineState::MouseMoveEvent(QPointF& currMousePos)
{
    if (mIsDrawing)
    {
       mScene->MoveDrawingPoint(currMousePos);
    }

}

void scDrawLineState::MouseReleaseEvent()
{
}

void scDrawLineState::KeyPressEvent()
{
    if (mIsDrawing)
    {
        mScene->EndDrawing();
        mIsDrawing = false;
    }
}
