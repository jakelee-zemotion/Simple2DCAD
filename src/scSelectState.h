#pragma once
#include "scState.h"
#include "scShapeQtVisual.h"
#include <memory>

class scSelectState : public scState
{
public:
	scSelectState(std::shared_ptr<scScene>& scene, SELECT selectShapeType);
	~scSelectState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	bool mIsMousePressed;
	SELECT mSelectShapeType;


	std::shared_ptr<scShapeQtVisual> mPrevShape;
	std::shared_ptr<scShapeQtVisual> mCurrShape;
};

