#pragma once
#include "scVertexVisualInterface.h"

#include <memory>

class scLineData
{
public:
	scLineData();
	~scLineData();

	void SetStartVertex(std::shared_ptr<scVertexVisualInterface> startVertex);
	void SetEndVertex(std::shared_ptr<scVertexVisualInterface> endVertex);

	double GetStartX() const;
	double GetStartY() const;
	double GetEndX() const;
	double GetEndY() const;

private:
	std::shared_ptr<scVertexVisualInterface> mStartVertex;
	std::shared_ptr<scVertexVisualInterface> mEndVertex;
};

