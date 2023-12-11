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
    if (!mIsDrawing)
    {
        // Put two points to create a line on the first click.
        // Therefore, the second point is adjusted in MouseMoveEvent.
        mScene.AddLine(currMousePos, currMousePos);
        mIsDrawing = true;
    }
    else
    {
        mScene.AddVertex(currMousePos);

        // Close testing
        // If CloseTest is true (i.e. if polygon can be created), Drawing mode is stopped.
        //mIsDrawing = !mScene.CloseTest(currMousePos);
    }
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
