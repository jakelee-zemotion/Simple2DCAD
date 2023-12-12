#include "scSelectState.h"

#include <qDebug>

using namespace std;

scSelectState::scSelectState(shared_ptr<scScene>& scene, SELECT selectShapeType)
	:scState(scene), mSelectShapeType(selectShapeType)
{
	mIsMousePressed = false;
	mPrevMousePos = { 0.0, 0.0 };
}

scSelectState::~scSelectState()
{
}

void scSelectState::MousePressEvent(const QPointF& currMousePos)
{
	mIsMousePressed = true;
	mPrevMousePos = currMousePos;
}

void scSelectState::MouseMoveEvent(const QPointF& currMousePos)
{
	mSelectedShape = mScene->HitTest(currMousePos, mSelectShapeType);

	// mSelectedShape != nullptr
	if (mSelectedShape.use_count())
	{


		if (mIsMousePressed)
		{
			QPointF dist = currMousePos - mPrevMousePos;
			mPrevMousePos = currMousePos;

			mSelectedShape->MoveShape(dist.x(), dist.y());
		}
	}
}

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;
	mSelectedShape.reset();
}

void scSelectState::KeyPressEvent()
{
}
