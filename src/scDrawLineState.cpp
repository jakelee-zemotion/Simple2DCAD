#include "scDrawLineState.h"


using namespace std;

scDrawLineState::scDrawLineState(shared_ptr<scScene>& scene)
    :scState(scene)
{
    mIsDrawing = false;
    mStartVertexPos = { 0.0, 0.0 };
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(const QPointF& currMousePos)
{
    // Put two points to create a line on the first click.
    // Therefore, the second point is adjusted in MouseMoveEvent.
    if (!mIsDrawing)
    {
        // Add and Return the vertex.
        mStartVertex = mScene->AddStartVertex(currMousePos);
        mStartVertexPos = currMousePos;
        mIsDrawing = true;
    }

    // Add and Return the vertex.
    mSelectedShape = mScene->AddEndVertex(currMousePos);

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const QPointF& currMousePos)
{
    if (mIsDrawing && mSelectedShape != nullptr)
    {
        QPointF targetPos = currMousePos;
        if (mScene->CanCreateFace() && mStartVertex->HitTest(currMousePos))
        {
            targetPos = mStartVertexPos;
        }

        QPointF dist = targetPos - mPrevMousePos;
        mPrevMousePos = targetPos;

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
        mStartVertex.reset();
    }
}
