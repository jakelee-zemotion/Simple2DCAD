#pragma once

// Simple2DCAD
#include "scState.h"

// Forward Declaration
class scScene;
class scVertexQtVisual;
class scShapeQtVisual;

class scDrawLineState : public scState
{
// [Member function section]
public:
	scDrawLineState(const std::shared_ptr<scScene>& scene, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scDrawLineState() override;

	void Paint(QPainter& painter) override;

	void MousePressEvent(const scVector2D& currMousePos) override;
	void MouseMoveEvent(const scVector2D& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

	void EndDrawing(const bool createFaceFlag);
	bool CanCreateFace(const scVector2D& currMousePos) const;

// [Member variable section]
private:
	std::shared_ptr<scVertexQtVisual> mDrawingVertex;
	std::shared_ptr<scVertexQtVisual> mDrawStartVertex;
	
	bool mIsDrawing;
};

