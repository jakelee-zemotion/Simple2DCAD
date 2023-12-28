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

void scDrawLineState::MousePressEvent(const scVector2D& currMousePos)
{
    // Create a Face.
    if (CanCreateFace(currMousePos))
    {
        this->EndDrawing(true);
        return;
    }

    // Put two points to create a line on the first click.
    // Therefore, the second point is adjusted in MouseMoveEvent.
    if (!mIsDrawing)
    {
        mDrawStartVertex = mScene->AddStartVertex(currMousePos);
        mIsDrawing = true;
    }

    // Add and Return the vertex.
    mDrawingVertex = mScene->AddEndVertex(currMousePos);

    mPrevMousePos = currMousePos;
}

void scDrawLineState::MouseMoveEvent(const scVector2D& currMousePos)
{
    if (mIsDrawing)
    {
        assert(mDrawingVertex != nullptr);

        scVector2D targetPos = SnapVertex(currMousePos, mDrawingVertex->GetID());

        mDrawingVertex->Move(targetPos);
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
