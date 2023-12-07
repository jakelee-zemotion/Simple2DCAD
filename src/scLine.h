#pragma once
#include <memory>

class scVertex;
class scLine
{
public:
	scLine(std::shared_ptr<scVertex>& startVertex, std::shared_ptr<scVertex>& endVertex);
	~scLine();

	scVertex GetStartVertex() const;
	scVertex GetEndVertex() const;

private:
	std::shared_ptr<scVertex> mStartVertex;
	std::shared_ptr<scVertex> mEndVertex;
};

