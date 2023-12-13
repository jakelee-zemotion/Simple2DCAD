#include "scDrawLineState.h"


using namespace std;

scDrawLineState::scDrawLineState(shared_ptr<scScene>& scene)
    :scState(scene)
{
    mStartVertexPos = { 0.0, 0.0 };
    mIsDrawing = false;
    mCanCreateFace = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(const QPointF& currMousePos)
{
    // Create a Face.
    if (mCanCreateFace)
    {
        mScene->EndDrawing();
        mIsDrawing = false;

        mCanCreateFace = false;
        return;
    }

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
        mCanCreateFace = false;

        if (mScene->CanCreateFace() && mStartVertex->HitTest(currMousePos))
        {
            targetPos = mStartVertexPos;
            mCanCreateFace = true;
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
        // KeyPress do not create a face.
        mCanCreateFace = false;

        mScene->EndDrawing();
        mIsDrawing = false;
    }
}
