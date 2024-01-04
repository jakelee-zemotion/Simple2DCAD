#include "scShapeQtVisual.h"

// qt
#include <QDebug>
#include <QPainter>

// Simple2DCAD
#include "scCoordinateHelper.h"

using namespace std;

scShapeQtVisual::scShapeQtVisual(const scShapeType& shapeType, const shared_ptr<scCoordinateHelper>& coordinateHelper)
    : mShapeType(shapeType), mCoordinateHelper(coordinateHelper), mHitSize(10.0)
{
    mShapeColorType = scColorType::DEFAULT;
    mShapeColors = vector<Qt::GlobalColor>(3, Qt::black);
}

scShapeQtVisual::~scShapeQtVisual()
{
}

void scShapeQtVisual::SetShapeColorType(const scColorType color)
{
    mShapeColorType = color;
}

scShapeType scShapeQtVisual::GetShapeType() const
{
    return mShapeType;
}