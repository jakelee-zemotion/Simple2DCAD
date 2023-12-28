#include "scSelectState.h"

#include "scScene.h"
#include "scShapeQtVisual.h"
#include "scVertexQtVisual.h"
#include "scFaceQtVisual.h"

#include <qDebug>
#include <QKeyEvent>

using namespace std;

scSelectState::scSelectState(const shared_ptr<scScene>& scene, SHAPE_TYPE selectShapeType)
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

	scVector2D pos = { currMousePos.x(), currMousePos.y() };

	if (mIsMousePressed)
	{
		if (mCurrHighlightShape == nullptr)
			return;
		
		QPointF targetPos = currMousePos;

		// Vertex snapping
		if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::VERTEX)
		{
			targetPos = SnapVertex(currMousePos, mCurrHighlightShape->GetID());
		}

		if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::FACE)
		{
			//double scaleX = currMousePos.x() / mPrevMousePos.x();
			//double scaleY = currMousePos.y() / mPrevMousePos.y();

			//shared_ptr<scFaceQtVisual> scaleFace = dynamic_pointer_cast<scFaceQtVisual>(mCurrShape);
			//scaleFace->ScaleFace(scaleX, scaleY);
			////qDebug() << currMousePos.x() << mPrevMousePos.x() << scaleX << scaleY;
			//mPrevMousePos = currMousePos;
			//return;
		}

		scVector2D aa = { targetPos.x(), targetPos.y() };
		scVector2D bb = { mPrevMousePos.x(), mPrevMousePos.y() };

		mCurrHighlightShape->Move(aa, bb);

		mPrevMousePos = currMousePos;

		return;
	}


	mCurrHighlightShape = mScene->HitTest(pos, mSelectShapeType);
	HightlightShape();
	
	mPrevHighlightShape = mCurrHighlightShape;
}

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;

	SelectShape();
}

void scSelectState::KeyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Escape:
		{
			ResetSelected();
		}
		break;
	}
}

void scSelectState::EndState()
{
	if (mPrevHighlightShape != nullptr)
		mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mCurrHighlightShape != nullptr)
		mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mPrevHighlightShape.reset();
	mCurrHighlightShape.reset();

	ResetSelected();
}

void scSelectState::ResetSelected()
{
	if (mSelectedShape == nullptr)
		return;

	mSelectedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
		mScene->RemoveBoundingBoxOfFace();

	mSelectedShape.reset();

}

void scSelectState::HightlightShape()
{
	// From outside to inside the shape.
	if (mPrevHighlightShape == nullptr && mCurrHighlightShape != nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mCurrHighlightShape->GetID())
			mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::HIGHTLIGHT);
	}
	// From inside the shape to outside.
	else if (mPrevHighlightShape != nullptr && mCurrHighlightShape == nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mPrevHighlightShape->GetID())
			mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}
	// From inside one shape to inside another shape.
	else if (mPrevHighlightShape != nullptr && mCurrHighlightShape != nullptr)
	{
		if (mPrevHighlightShape->GetID() == mCurrHighlightShape->GetID())
			return;

		// From inside the selected shape(previous shape) to inside the current shape.
		if (mSelectedShape != nullptr && mSelectedShape->GetID() == mPrevHighlightShape->GetID())
		{
			mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::HIGHTLIGHT);
		}
		// From inside the previous shape to inside the the selected shape(current shape).
		else if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
		{
			mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
		}
		// If there is not a selected shape.
		else
		{
			mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
			mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::HIGHTLIGHT);
		}		 

	}
}

void scSelectState::SelectShape()
{
	if (mCurrHighlightShape == nullptr)
		return;

	if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
		return;

	if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::SCALE_VERTEX
		|| mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::ROTATE_VERTEX)
		return;


	// Reset mSelectedShape
	if (mSelectedShape != nullptr && mSelectedShape->GetID() != mCurrHighlightShape->GetID())
		ResetSelected();

	// Set mSelectedShape
	mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::SELECT);
	mSelectedShape = mCurrHighlightShape;



	if (mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
	{
		shared_ptr<scFaceQtVisual> selectedFace =
			dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);

		mScene->AddBoundingBoxOfFace(selectedFace);
	}
}
