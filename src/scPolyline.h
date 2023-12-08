#pragma once
#include "scQtShapeInterface.h"
#include <memory>

class scQtVertex;
class scQtLine;
class scPolyline : public scQtShapeInterface
{
public:
	scPolyline(std::shared_ptr<scQtLine>& firstLine);
	virtual ~scPolyline() override;

	void Paint(QPainter& painter) override;
	void AddSharedLine(std::shared_ptr<scQtLine>& line);

private:
	std::list<std::shared_ptr<scQtLine>> mSharedLineList;
	QList<QPointF> mVertexList;
};

