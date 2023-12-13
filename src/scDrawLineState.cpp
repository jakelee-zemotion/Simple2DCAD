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
    // Put two points to create a line on the first click.
    // Therefore, the second point is adjusted in MouseMoveEvent.
    if (!mIsDrawing)
    {
        // Return the added vertex.
        mStartVertex = mScene->AddStartVertex(currMousePos);
        mIsDrawing = true;
    }

    // Return the added vertex.
    mSelectedShape = mScene->AddEndVertex(currMousePos);

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const QPointF& currMousePos)
{
    

    if (mIsDrawing && mSelectedShape != nullptr)
    {
        QPointF dist = currMousePos - mPrevMousePos;
        mPrevMousePos = currMousePos;

        mSelectedShape->MoveShape(dist.x(), dist.y());


        if (mScene->CanCreateFace())
        {
            mCurrShape = mScene->HitTest(currMousePos, SELECT::VERTEX);

            if (mPrevShape == nullptr && mCurrShape != nullptr)
            {
                mCurrShape->SetColor(Qt::red);
            }
            else if (mPrevShape != nullptr && mCurrShape == nullptr)
            {
                mPrevShape->SetColor(Qt::black);
            }
            else if (mPrevShape != nullptr && mCurrShape != nullptr)
            {
                if (mPrevShape->GetID() == mCurrShape->GetID())
                    return;

                mPrevShape->SetColor(Qt::black);
                mCurrShape->SetColor(Qt::red);
            }

            mPrevShape = mCurrShape;
        }
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
