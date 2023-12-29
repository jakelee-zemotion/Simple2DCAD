#pragma once


#ifndef SC_COMMON_H
#define SC_COMMON_H

enum class SHAPE_TYPE
{
	VERTEX = 1, LINE = 2, FACE = 4, ROTATE_CONTROL_VERTEX = 8, SCALE_CONTROL_VERTEX = 16, CENTER_CONTROL_VERTEX = 32
};

inline SHAPE_TYPE operator|(SHAPE_TYPE stype1, SHAPE_TYPE stype2)
{
	int result = static_cast<int>(stype1) | static_cast<int>(stype2);
	return static_cast<SHAPE_TYPE>(result);
}

inline int operator>>(SHAPE_TYPE stype, int value)
{
	return static_cast<int>(stype) >> value;
}

inline bool operator==(SHAPE_TYPE stype1, SHAPE_TYPE stype2)
{
	return static_cast<int>(stype1) & static_cast<int>(stype2);
}

enum class COLOR_TYPE
{
	DEFAULT, HIGHTLIGHT, SELECT
};


enum class BOX_POSITION
{
	TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT
};

#endif