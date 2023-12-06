#include "SelectState.h"
#include "ShapeVector.h"

#include <qDebug>

SelectState::SelectState(ShapeVector& shapeObjects)
	:mShapeObjects(shapeObjects)
{
	mIsPressed = false;
}

SelectState::~SelectState()
{
}

void SelectState::MousePressEvent(QPoint& currMousePos)
{
	mIsPressed = true;

	for (const auto& object : mShapeObjects.mShapes)
	{
		for (auto& point : object->mPoints)
		{
			if (mShapeObjects.IsObjectClosed(point, currMousePos))
			{
				qDebug() << "hit";
				mSelectedPoint = &point;//std::make_shared<QPoint>(point);
			}

		}
	}
}

void SelectState::MouseMoveEvent(QPoint& currMousePos)
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

void SelectState::MouseReleaseEvent()
{
	mIsPressed = false;

	mSelectedPoint = nullptr;
}

void SelectState::KeyPressEvent()
{
}
