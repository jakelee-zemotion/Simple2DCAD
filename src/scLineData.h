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

	void SetStartVertex(double x, double y);
	void SetEndVertex(double x, double y);

	double GetStartX() const;
	double GetStartY() const;
	double GetEndX() const;
	double GetEndY() const;

private:
	std::shared_ptr<scVertexVisualInterface> mStartVertex;
	std::shared_ptr<scVertexVisualInterface> mEndVertex;
};

