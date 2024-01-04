#include "scShapeQtVisual.h"
#include "scCoordinateHelper.h"

#include <qDebug>
#include <QPainter>

using namespace std;

scShapeQtVisual::scShapeQtVisual(const scShapeType& shapeType, const shared_ptr<scCoordinateHelper>& coordinateHelper)
    : mShapeType(shapeType), mCoordinateHelper(coordinateHelper)
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