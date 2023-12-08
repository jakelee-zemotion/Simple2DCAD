#pragma once
#include <memory>
#include <QPointF>

class scQtVertex;
class scLine
{
public:
	scLine(std::shared_ptr<scQtVertex>& startVertex, std::shared_ptr<scQtVertex>& endVertex);
	~scLine();

	scQtVertex GetStartVertex() const;
	scQtVertex GetEndVertex() const;

private:
	std::shared_ptr<scQtVertex> mStartVertex;
	std::shared_ptr<scQtVertex> mEndVertex;
};

