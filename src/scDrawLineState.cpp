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
    mScene->AddVertex(currMousePos, mIsDrawing);
    mIsDrawing = true;

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const QPointF& currMousePos)
{
    if (mIsDrawing)
    {
        QPointF dist = currMousePos - mPrevMousePos;
        mPrevMousePos = currMousePos;

        //mSelectedPoint->MoveShape(dist.x(), dist.y());
        mScene->MoveVertex(currMousePos);
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
