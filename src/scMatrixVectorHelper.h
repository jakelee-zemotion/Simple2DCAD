#pragma once

// system
#include <cmath>

struct scVector2D
{
	double x, y, z;

	scVector2D() : x(0.0), y(0.0), z(0.0) {}
	scVector2D(double _x, double _y) : x(_x), y(_y), z(1.0) {}
	scVector2D(const scVector2D& v) : x(v.x), y(v.y), z(1.0) {}
	scVector2D& operator=(const scVector2D& v) 
	{ 
		x = v.x; 
		y = v.y; 
		z = 1.0; 

		return *this; 
	}
};

inline scVector2D operator+(const scVector2D& v0, const scVector2D& v1)
{
	return { v0.x + v1.x, v0.y + v1.y };
}

inline scVector2D operator-(const scVector2D& v0, const scVector2D& v1)
{
	return { v0.x - v1.x, v0.y - v1.y };
}

inline scVector2D operator/(const scVector2D& v0, const scVector2D& v1)
{
	return { v0.x / v1.x, v0.y / v1.y };
}

inline scVector2D& operator+=(scVector2D& v0, const scVector2D& v1)
{
	v0.x += v1.x;
	v0.y += v1.y;

	return v0;
}

inline scVector2D& operator-=(scVector2D& v0, const scVector2D& v1)
{
	v0.x -= v1.x;
	v0.y -= v1.y;

	return v0;
}

namespace scVectorHelper
{
	inline double length(const scVector2D& v0, const scVector2D& v1)
	{
		return sqrt((v0.x - v1.x) * (v0.x - v1.x) + (v0.y - v1.y) * (v0.y - v1.y));
	}

	inline double crossZ(const scVector2D& v0, const scVector2D& v1)
	{
		return v0.x * v1.y - v0.y * v1.x;
	}
}

struct scMatrix2D
{
	double m[3][3];
}; 

inline scMatrix2D operator*(const scMatrix2D& a, const scMatrix2D& b)
{
	scMatrix2D c;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c.m[i][j] = 0.0;
			for (int k = 0; k < 3; k++)
			{
				c.m[i][j] += a.m[i][k] * b.m[k][j];
			}

		}
	}

	return c;
}

inline scVector2D operator*(const scMatrix2D& A, const scVector2D& v)
{
	scVector2D b;

	// b[i] += A.m[i][j] * v[j]
	b.x += A.m[0][0] * v.x;
	b.x += A.m[0][1] * v.y;
	b.x += A.m[0][2] * v.z;

	b.y += A.m[1][0] * v.x;
	b.y += A.m[1][1] * v.y;
	b.y += A.m[1][2] * v.z;

	b.z += A.m[2][0] * v.x;
	b.z += A.m[2][1] * v.y;
	b.z += A.m[2][2] * v.z;

	return b;
}

namespace scMatrixHelper
{
	inline scMatrix2D IdentityMatrix()
	{
		return
		{
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		};
	}

	inline scMatrix2D TranslateMatrix(const scVector2D& d)
	{
		return
		{
			1.0, 0.0, d.x,
			0.0, 1.0, d.y,
			0.0, 0.0, 1.0
		};
	}

	inline scMatrix2D InverseTranslateMatrix(const scVector2D& d)
	{
		return
		{
			1.0, 0.0, -d.x,
			0.0, 1.0, -d.y,
			0.0, 0.0,  1.0
		};
	}

	inline scMatrix2D ScaleMatrix(const scVector2D& s)
	{
		return
		{
			s.x, 0.0, 0.0,
			0.0, s.y, 0.0,
			0.0, 0.0, 1.0
		};
	}

	inline scMatrix2D InverseScaleMatrix(const scVector2D& s)
	{
		return
		{
			1.0 / s.x, 0.0      , 0.0,
			0.0      , 1.0 / s.y, 0.0,
			0.0      , 0.0      , 1.0
		};
	}

	inline scMatrix2D RotateMatrix(const double theta)
	{
		return
		{
			 cos(theta), -sin(theta),  0.0,
			 sin(theta),  cos(theta),  0.0,
			        0.0,         0.0,  1.0
		};
	}

	inline scMatrix2D InverseRotateMatrix(const double theta)
	{
		return
		{
			 cos(theta),  sin(theta),  0.0,
			-sin(theta),  cos(theta),  0.0,
			        0.0,         0.0,  1.0
		};
	}
}