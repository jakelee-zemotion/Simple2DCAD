#pragma once
#include "scShapeInterface.h"
#include <memory>

class scLine;
class scPolyline : public scShapeInterface
{
public:
	scPolyline(std::shared_ptr<scLine>& firstLine);
	virtual ~scPolyline() override;

	void Paint(QPainter& painter) override;
	void AddSharedLine(std::shared_ptr<scLine>& line);

private:
	std::list<std::shared_ptr<scLine>> mSharedLineList;

};

