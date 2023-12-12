#include "scDrawLineState.h"
#include "scScene.h"

#include <QPointF>

scDrawLineState::scDrawLineState(scScene& scene)
    :scState(scene)
{
    mIsDrawing = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(QPointF& currMousePos)
{
    mScene.AddVertex(currMousePos, mIsDrawing);
    mIsDrawing = true;
}

void scDrawLineState::MouseMoveEvent(QPointF& currMousePos)
{
    if (mIsDrawing)
    {
       mScene.MoveDrawingPoint(currMousePos);
    }

}

void scDrawLineState::MouseReleaseEvent()
{
}

void scDrawLineState::KeyPressEvent()
{
    if (mIsDrawing)
    {
        mScene.EndDrawing();
        mIsDrawing = false;
    }
}
