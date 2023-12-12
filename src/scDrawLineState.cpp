#include "scDrawLineState.h"

#include <QPointF>

using namespace std;

scDrawLineState::scDrawLineState(shared_ptr<scScene>& scene)
    :scState(scene)
{
    mIsDrawing = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(const QPointF& currMousePos)
{
    // Return the added vertex.
    mSelectedShape = mScene->AddVertex(currMousePos, mIsDrawing);
    mIsDrawing = true;

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const QPointF& currMousePos)
{
    if (mIsDrawing && mSelectedShape.use_count())
    {
        QPointF dist = currMousePos - mPrevMousePos;
        mPrevMousePos = currMousePos;

        mSelectedShape->MoveShape(dist.x(), dist.y());
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

        mSelectedShape.reset();
    }
}
