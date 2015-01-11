#include "Matrix4D.h"
#include <stdexcept>

namespace Math
{

	Matrix4D::Matrix4D()
	{
		for(auto i = 0; i < 4; i++)
			for(auto j = 0; j < 4; j++)
				data[i][j] = 0;
	}

	void Matrix4D::loadIdendity()
	{
		for(auto i = 0; i < 4; i++)
			data[i][i] = 1;
	}

	void Matrix4D::setRow(int nbr, Vector4D& row)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for nbr is: 0 <= x <= 3!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			data[nbr][i] = row[i];
	}

	void Matrix4D::setColumn(int nbr, Vector4D& col)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for nbr is: 0 <= x <= 3!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			data[i][nbr] = col[i];
	}

	Vector4D Matrix4D::getRow(int nbr)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for nbr is: 0 <= x <= 3!");

		Vector4D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			v[i] = data[nbr][i];

		return v;
	}

	Vector4D Matrix4D::getColumn(int nbr)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for nbr is: 0 <= x <= 3!");

		Vector4D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			v[i] = data[i][nbr];

		return v;
	}

	Matrix4D&Matrix4D::operator+(const Matrix4D& m)
	{
		for(auto i = 0; i < 4; i++)
			for(auto j = 0; j < 4; j++)
				data[i][j]+= m.data[i][j];
	}

	Matrix4D&Matrix4D::operator-(const Matrix4D& m)
	{
		for(auto i = 0; i < 4; i++)
			for(auto j = 0; j < 4; j++)
				data[i][j]-= m.data[i][j];
	}




	//----------------------------------------------------------------------------------------------



	Matrix4D idendity()
	{
		Matrix4D m;
		m.loadIdendity();
		return m;
	}

}
