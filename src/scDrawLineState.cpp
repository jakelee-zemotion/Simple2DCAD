#include "scDrawLineState.h"
#include "scShapeVector.h"

#include <QPoint>

scDrawLineState::scDrawLineState(scShapeVector& shapeObjects)
    :mShapeObjects(shapeObjects)
{
    mIsDrawing = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(QPoint& currMousePos)
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

void scDrawLineState::MouseMoveEvent(QPoint& currMousePos)
{
    if (mIsDrawing)
    {
        mShapeObjects.SetLastPoint(currMousePos);
    }

}

void scDrawLineState::MouseReleaseEvent()
{
}

void scDrawLineState::KeyPressEvent()
{
    if (mIsDrawing)
    {
        mShapeObjects.CheckLastShape();
        mIsDrawing = false;
    }
}
