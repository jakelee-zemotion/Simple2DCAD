#include "scState.h"

#include "scScene.h"
#include "scVertexQtVisual.h"
#include "scShapeID.h"

using namespace std;

scState::scState(const shared_ptr<scScene>& scene)
	:mScene(scene)
{
}

scState::~scState()
{
}


scVector2D scState::SnapVertex(const scVector2D& currMousePos, const scShapeID& noTestShapeID)
{
	shared_ptr<scShapeQtVisual> hitTestResultVertex =
		mScene->HitTest(currMousePos, SHAPE_TYPE::VERTEX, noTestShapeID);

	shared_ptr<scVertexQtVisual> snappedVertex =
		dynamic_pointer_cast<scVertexQtVisual>(hitTestResultVertex);

	if (snappedVertex != nullptr)
		return snappedVertex->GetXY();
	else
		return currMousePos;
}