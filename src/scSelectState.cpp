#include "scSelectState.h"

#include <qDebug>

using namespace std;

scSelectState::scSelectState(shared_ptr<scScene>& scene, SELECT selectShapeType)
	:scState(scene), mSelectShapeType(selectShapeType)
{
	mIsPressed = false;
	mPrevMousePos = { 0.0, 0.0 };
}

scSelectState::~scSelectState()
{
}

void scSelectState::MousePressEvent(const QPointF& currMousePos)
{
	mIsPressed = true;
	mPrevMousePos = currMousePos;

	mSelectedShape = mScene->HitTest(currMousePos, mSelectShapeType);
}

void scSelectState::MouseMoveEvent(const QPointF& currMousePos)
{
				   // mSelectedShape != nullptr
	if (mIsPressed && mSelectedShape.use_count())
	{
		QPointF dist = currMousePos - mPrevMousePos;
		mPrevMousePos = currMousePos;

		mSelectedShape->MoveShape(dist.x(), dist.y());
	}
}

void scSelectState::MouseReleaseEvent()
{
	mIsPressed = false;
	mSelectedShape.reset();
}

void scSelectState::KeyPressEvent()
{
}
