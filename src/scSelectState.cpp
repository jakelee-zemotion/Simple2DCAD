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

void scSelectState::MousePressEvent(QPoint& currMousePos)
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
	}
}

void scSelectState::MouseMoveEvent(QPoint& currMousePos)
{
	if (mIsPressed)
	{
		//qDebug() << mSelectedPoint.use_count();

		if (mSelectedPoint != nullptr)
		{
			*mSelectedPoint = currMousePos;
		}
	}
}

void scSelectState::MouseReleaseEvent()
{
	mIsPressed = false;

	mSelectedPoint = nullptr;
}

void scSelectState::KeyPressEvent()
{
}
