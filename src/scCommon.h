#pragma once

// State Names
#define SC_DRAW_LINE     "DrawLine"
#define SC_SELECT_ALL    "SelectAll"
#define SC_SELECT_VERTEX "SelectVertex"
#define SC_SELECT_LINE   "SelectLine"
#define SC_SELECT_FACE   "SelectFace"

// File Directory
#define SC_IMAGE_DIRECTORY "C:/Users/Jake/Desktop/code/Simple2DCAD/img/"

enum class scShapeType
{
	VERTEX = 1, LINE = 2, FACE = 4, ROTATE_CONTROL_VERTEX = 8, SCALE_CONTROL_VERTEX = 16, CENTER_CONTROL_VERTEX = 32
};

inline scShapeType operator|(const scShapeType stype0, const scShapeType stype1)
{
	int result = static_cast<int>(stype0) | static_cast<int>(stype1);
	return static_cast<scShapeType>(result);
}

inline int operator>>(const scShapeType stype, const int value)
{
	return static_cast<int>(stype) >> value;
}

inline bool operator==(const scShapeType stype0, const scShapeType stype1)
{
	return static_cast<int>(stype0) & static_cast<int>(stype1);
}

enum class scColorType
{
	DEFAULT, HIGHTLIGHT, SELECT
};

enum class scBoxPosition
{
	TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT
};