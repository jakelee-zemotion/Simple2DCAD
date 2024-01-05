#include "scState.h"

// Simple2DCAD
#include "scScene.h"
#include "scVertexQtVisual.h"
#include "scShapeID.h"
#include "scCoordinateHelper.h"

using namespace std;

scState::scState(const shared_ptr<scScene>& scene, const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
		:mScene(scene), mCoordinateHelper(coordinateHelper)
{
}

scState::~scState()
{
}

scVector2D scState::SnapVertex(const scVector2D& currMousePos, const scShapeID& noTestShapeID)
{
	const shared_ptr<scShapeQtVisual> hitTestResultVertex = mScene->HitTest(currMousePos, scShapeType::VERTEX, noTestShapeID);
	const shared_ptr<scVertexQtVisual> snappedVertex = dynamic_pointer_cast<scVertexQtVisual>(hitTestResultVertex);

	if (snappedVertex != nullptr)
		return snappedVertex->GetXY();
	else
		return currMousePos;
}