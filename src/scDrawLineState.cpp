#include "scDrawLineState.h"
#include "scShapeList.h"

#include <QPointF>

scDrawLineState::scDrawLineState(scShapeList& shapeObjects)
    :mShapeObjects(shapeObjects)
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
        mShapeObjects.AddLine(currMousePos, currMousePos);
        mIsDrawing = true;
    }
    else
    {
        mShapeObjects.AddVertex(currMousePos);

        // Close testing
        // If CloseTest is true (i.e. if polygon can be created), Drawing mode is stopped.
        //mIsDrawing = !mShapeObjects.CloseTest(currMousePos);
    }
}

void scDrawLineState::MouseMoveEvent(QPointF& currMousePos)
{
    if (mIsDrawing)
    {
       mShapeObjects.MoveDrawingPoint(currMousePos);
    }

}

void scDrawLineState::MouseReleaseEvent()
{
}

void scDrawLineState::KeyPressEvent()
{
    if (mIsDrawing)
    {
        mShapeObjects.EndDrawing();
        mIsDrawing = false;
    }
}
