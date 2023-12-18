#pragma once
#include "scVertexData.h"

#include <memory>

class scLineData
{
public:
	scLineData();
	~scLineData();

	void SetStartVertex(const std::shared_ptr<scVertexData>& startVertex);
	void SetEndVertex(const std::shared_ptr<scVertexData>& endVertex);

	void SetStartVertex(double x, double y);
	void SetEndVertex(double x, double y);

	double GetStartX() const;
	double GetStartY() const;
	double GetEndX() const;
	double GetEndY() const;

	double GetStartScaleX() const;
	double GetStartScaleY() const;
	double GetEndScaleX() const;
	double GetEndScaleY() const;

private:
	std::shared_ptr<scVertexData> mStartVertex;
	std::shared_ptr<scVertexData> mEndVertex;
};

