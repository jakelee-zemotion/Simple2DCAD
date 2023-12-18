#include "scShapeQtVisual.h"

#include <qDebug>

using namespace std;

scShapeQtVisual::scShapeQtVisual(SHAPE_TYPE shapeType, const shared_ptr<scCoordinate>& coordinate)
    : mShapeType(shapeType), mCoordinate(coordinate), mHitSize(10.0)
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