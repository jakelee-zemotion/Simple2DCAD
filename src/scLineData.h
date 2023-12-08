#pragma once
#include "scVertexInterface.h"

#include <memory>

class scLineData
{
public:
	scLineData();
	~scLineData();

	void SetStartVertex(std::shared_ptr<scVertexInterface> startVertex);
	void SetEndVertex(std::shared_ptr<scVertexInterface> endVertex);

	double GetStartX() const;
	double GetStartY() const;
	double GetEndX() const;
	double GetEndY() const;

private:
	std::shared_ptr<scVertexInterface> mStartVertex;
	std::shared_ptr<scVertexInterface> mEndVertex;
};

