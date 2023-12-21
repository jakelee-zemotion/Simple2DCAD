#include "scDrawLineState.h"
#include "scShapeQtVisual.h"
#include "scScene.h"

#include <QKeyEvent>

using namespace std;

scDrawLineState::scDrawLineState(const shared_ptr<scScene>& scene)
    :scState(scene)
{
    mStartVertexPos = { 0.0, 0.0 };
    mIsDrawing = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(const QPointF& currMousePos)
{
    // Create a Face.
    if (CanCreateFace(currMousePos))
    {
        // Reset the shared pointers.
        mDrawingShape.reset();
        mDrawStartVertex.reset();

        mScene->EndDrawing(true);

        mIsDrawing = false;
        return;
    }

    // Put two points to create a line on the first click.
    // Therefore, the second point is adjusted in MouseMoveEvent.
    if (!mIsDrawing)
    {
        mDrawStartVertex = mScene->AddStartVertex(currMousePos);
        mStartVertexPos = currMousePos;
        mIsDrawing = true;
    }

    // Add and Return the vertex.
    mDrawingShape = mScene->AddEndVertex(currMousePos);

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const QPointF& currMousePos)
{
    if (mIsDrawing)
    {
        assert(mDrawingShape != nullptr);

        QPointF targetPos = currMousePos;

        if (CanCreateFace(currMousePos))
        {
            targetPos = mStartVertexPos;
        }

        mDrawingShape->Move(targetPos.x(), targetPos.y());
    }

}

void scDrawLineState::MouseReleaseEvent()
{
}

void scDrawLineState::KeyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Escape:
        {
            EndState();
        }
        break;
    }
}

void scDrawLineState::EndState()
{
    if (mIsDrawing)
    {
        // Reset the shared pointers.
        mDrawingShape.reset();
        mDrawStartVertex.reset();

        // KeyPress do not create a face.
        mScene->EndDrawing(false);

        mIsDrawing = false;
    }
}

bool scDrawLineState::CanCreateFace(const QPointF& currMousePos) const
{
    return
        mScene->GetVertexCreatedCount() >= 3
        && mDrawStartVertex != nullptr
        && mDrawStartVertex->HitTest(currMousePos);
}
