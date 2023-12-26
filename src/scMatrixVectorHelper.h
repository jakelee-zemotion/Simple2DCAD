#pragma once

#ifndef SC_MATRIX_VECTOR_HELPER_H
#define SC_MATRIX_VECTOR_HELPER_H

struct scMatrix2D
{
	double m[3][3];

	/*double m00, m01, m02;
	double m10, m11, m12;
	double m20, m21, m22;*/

	/*scMatrix2D()
	{
		m00 = 1.0, m01 = 0.0, m02 = 0.0;
		m10 = 0.0, m11 = 1.0, m12 = 0.0;
		m20 = 0.0, m21 = 0.0, m22 = 1.0;
	}*/


	inline scMatrix2D operator*(const scMatrix2D& b)
	{
		scMatrix2D c;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				c.m[i][j] = 0.0;
				for (int k = 0; k < 3; k++)
				{
					c.m[i][j] += m[i][k] * b.m[k][j];
				}

			}
		}

		return c;
	}

}; 

struct scVector2D
{
	double x, y, z;

	scVector2D(double _x, double _y) : x(_x), y(_y), z(1.0) {}
};


namespace MatrixHelper
{
	inline scMatrix2D GetIdentityMatrix()
	{
		return
		{
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		};
	}

	inline scMatrix2D GetTranslateMatrix(double dx, double dy)
	{
		return
		{
			1.0, 0.0,  dx,
			0.0, 1.0,  dy,
			0.0, 0.0, 1.0
		};
	}
}

#endif