#include "Matrix4D.h"

namespace Math
{

	Matrix4D::Matrix4D()
	{
		for(auto i = 0; i < 4; i++)
			for(auto j = 0; j < 4; j++)
				data[i][j] = 0;
	}

	void Matrix4D::setRow(int nbr, Vector4D& row)
	{

	}

	void Matrix4D::setColumn(int nbr, Vector4D& col)
	{

	}

	void Matrix4D::loadIdendity()
	{
		for(auto i = 0; i < 4; i++)
			data[i][i] = 1;
	}

	Vector4D Matrix4D::getRow(int nbr)
	{

	}

	Vector4D Matrix4D::getColumn(int nbr)
	{

	}

	Matrix4D idendity()
	{
		Matrix4D m;
		m.loadIdendity();
		return m;
	}

}
