#include "scDrawLineState.h"
#include "scVertexQtVisual.h"
#include "scShapeQtVisual.h"
#include "scScene.h"

#include <QKeyEvent>

using namespace std;

scDrawLineState::scDrawLineState(const shared_ptr<scScene>& scene)
    :scState(scene)
{
    mIsDrawing = false;
}

scDrawLineState::~scDrawLineState()
{
}

void scDrawLineState::MousePressEvent(const QPointF& currMousePos)
{
    scVector2D pos = { currMousePos.x(), currMousePos.y() };

    // Create a Face.
    if (CanCreateFace(pos))
    {
        this->EndDrawing(true);
        return;
    }

    // Put two points to create a line on the first click.
    // Therefore, the second point is adjusted in MouseMoveEvent.
    if (!mIsDrawing)
    {
        mDrawStartVertex = mScene->AddStartVertex(pos);
        mIsDrawing = true;
    }

    // Add and Return the vertex.
    mDrawingVertex = mScene->AddEndVertex(pos);

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const QPointF& currMousePos)
{
    if (mIsDrawing)
    {
        assert(mDrawingVertex != nullptr);

        QPointF targetPos = SnapVertex(currMousePos, mDrawingVertex->GetID());

        scVector2D aa = { targetPos.x(), targetPos.y() };

        mDrawingVertex->Move(aa);
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
            this->EndDrawing(false);
        }
        break;
    }
}

void scDrawLineState::EndState()
{
    this->EndDrawing(false);
}

void scDrawLineState::EndDrawing(bool createFaceFlag)
{
    if (mIsDrawing)
    {
        // Reset the shared pointers.
        mDrawingVertex.reset();
        mDrawStartVertex.reset();

        mScene->EndDrawing(createFaceFlag);

        mIsDrawing = false;
    }
}

bool scDrawLineState::CanCreateFace(const scVector2D& currMousePos) const
{
    return
        mScene->GetVertexCreatedCount() >= 3
        && mDrawStartVertex != nullptr
        && mDrawStartVertex->HitTest(currMousePos);
}
