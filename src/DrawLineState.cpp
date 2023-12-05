#include "DrawLineState.h"
#include "ShapeList.h"

#include <QPoint>

DrawLineState::DrawLineState(ShapeList& shapeObjects)
    :State(shapeObjects)
{
    mIsDrawing = false;
}

DrawLineState::~DrawLineState()
{
}

void DrawLineState::MousePressEvent(QPoint& currMousePos)
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

void DrawLineState::MouseMoveEvent(QPoint& currMousePos)
{
    if (mIsDrawing)
    {
        mShapeObjects.SetLastPoint(currMousePos);
    }

}

void DrawLineState::KeyPressEvent()
{
    mShapeObjects.CheckLastShape();
    mIsDrawing = false;
}
