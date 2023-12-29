#pragma once
#include "scVertexData.h"

#include <memory>

class scLineData
{
public:
	scLineData();
	~scLineData();

	void AddDeltaToStart(const scVector2D& delta);
	void AddDeltaToEnd(const scVector2D& delta);

	void SetStartVertex(const std::shared_ptr<scVertexData>& startVertex);
	void SetEndVertex(const std::shared_ptr<scVertexData>& endVertex);

	void SetPosToStartVertex(const scVector2D& pos);
	void SetPosToEndVertex(const scVector2D& pos);

	scVector2D GetStartPos() const;
	scVector2D GetEndPos() const;

	scTransform& GetStartTransform();
	scTransform& GetEndTransform();

private:
	std::shared_ptr<scVertexData> mStartVertex;
	std::shared_ptr<scVertexData> mEndVertex;
};

