#include "scShapeQtVisual.h"
#include "scCoordinateHelper.h"

#include <qDebug>

using namespace std;

scShapeQtVisual::scShapeQtVisual(const SHAPE_TYPE& shapeType, const shared_ptr<scCoordinateHelper>& coordinateHelper)
    : mShapeType(shapeType), mCoordinateHelper(coordinateHelper)
{
    mShapeColorType = COLOR_TYPE::DEFAULT;
    mShapeColors = vector<Qt::GlobalColor>(3, Qt::black);
}

scShapeQtVisual::~scShapeQtVisual()
{
}

void scShapeQtVisual::SetShapeColorType(const COLOR_TYPE color)
{
    mShapeColorType = color;
}

SHAPE_TYPE scShapeQtVisual::GetShapeType() const
{
    return mShapeType;
}

scShapeID scShapeQtVisual::GetID() const
{
    return mShapeID;
}