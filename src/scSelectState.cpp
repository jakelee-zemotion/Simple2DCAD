#include "scSelectState.h"
#include "scShapeList.h"

#include <qDebug>

scSelectState::scSelectState(scShapeList& shapeObjects)
	:mShapeObjects(shapeObjects)
{
	mIsPressed = false;
}

scSelectState::~scSelectState()
{
}

void scSelectState::MousePressEvent(QPointF& currMousePos)
{
	mIsPressed = true;

	for (const auto& point : mShapeObjects.mVertexList)
	{
		//for (auto& point : object->mPoints)
		//{
			//if (mShapeObjects.IsObjectClosed(*point.get(), currMousePos))
			//{
			//	qDebug() << "hit";
			//	mSelectedPoint = &point;//std::make_shared<QPoint>(point);
			//}
		//}

		if (point->HitTest(currMousePos))
		{
			mSelectedPoint = point;
		}
	}
}

void scSelectState::MouseMoveEvent(QPointF& currMousePos)
{
	if (mIsPressed)
	{
		//qDebug() << mSelectedPoint.use_count();

		if (mSelectedPoint.use_count())
		{
			mSelectedPoint->SetX(currMousePos.x());
			mSelectedPoint->SetY(currMousePos.y());
		}
	}
}

void scSelectState::MouseReleaseEvent()
{
	mIsPressed = false;

	mSelectedPoint.reset();
}

void scSelectState::KeyPressEvent()
{
}
