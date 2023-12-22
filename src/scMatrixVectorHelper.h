#pragma once

#ifndef SC_MATRIX_VECTOR_HELPER_H
#define SC_MATRIX_VECTOR_HELPER_H


struct scMatrix2D
{
	double m00, m01, m02;
	double m10, m11, m12;
	double m20, m21, m22;
};

struct scVector2D
{
	double x, y, z;

	scVector2D(double _x, double _y) : x(_x), y(_y), z(1.0) {}
};



#endif