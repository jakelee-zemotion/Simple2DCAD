#pragma once
#include <memory>
#include <QPointF>

class scVertex;
class scLine
{
public:
	scLine(std::shared_ptr<scVertex>& startVertex, std::shared_ptr<scVertex>& endVertex);
	~scLine();

	QPointF GetStartVertex() const;
	QPointF GetEndVertex() const;

private:
	std::shared_ptr<scVertex> mStartVertex;
	std::shared_ptr<scVertex> mEndVertex;
};

