#pragma once

class scCamera;
class QRect;
class scGrid
{
public:
	scGrid(const QRect& viewportSize);
	~scGrid();

private:
	const QRect& mViewportSize;
};

