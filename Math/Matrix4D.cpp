#include "Matrix4D.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

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
			throw std::out_of_range("Range for Matrix4D is: 0 <= x <= 3!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			data[nbr][i] = row[i];
	}

	void Matrix4D::setColumn(int nbr, Vector4D& col)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for Matrix4D is: 0 <= x <= 3!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			data[i][nbr] = col[i];
	}

	Vector4D Matrix4D::getRow(int nbr)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for Matrix4D is: 0 <= x <= 3!");

		Vector4D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			v[i] = data[nbr][i];

		return v;
	}

	Vector4D Matrix4D::getColumn(int nbr)
	{
		if(nbr < 0 || nbr >= 4)
			throw std::out_of_range("Range for Matrix4D is: 0 <= x <= 3!");

		Vector4D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 4; i++)
			v[i] = data[i][nbr];

		return v;
	}

	float Matrix4D::at(int row, int col) const
	{
		if(row < 0 || row >= 4 || col < 0 || col >= 4)
			throw std::out_of_range("Range for Matrix4D is: 0 <= x <= 3!");

		return data[row][col];
	}

	float&Matrix4D::at_ref(int row, int col)
	{
		if(row < 0 || row >= 4 || col < 0 || col >= 4)
			throw std::out_of_range("Range for Matrix4D is: 0 <= x <= 3!");

		return data[row][col];
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

	void Matrix4D::print() const
	{
		for(auto i = 0; i < 4; i++)
		{
			for(auto j = 0; j < 4; j++)
			{
				std::cout << data[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}




	//----------------------------------------------------------------------------------------------



	Matrix4D idendity()
	{
		Matrix4D m;
		m.loadIdendity();
		return m;
	}

	Matrix4D translate(Vector3D& v)
	{
		Matrix4D m;
		m.loadIdendity();
		for(auto i = 0; i < 3; i++)
			m.at_ref(i, 3) = v[i];

		return m;
	}

	Matrix4D translate(float x, float y, float z)
	{
		Vector3D v(x,y,z);
		return translate(v);
	}

	Matrix4D scale(Vector3D& v)
	{
		Matrix4D m;
		m.loadIdendity();

		for(auto i = 0; i < 3; i++)
			m.at_ref(i, i) = v[i];

		return m;
	}

	Matrix4D scale(float x, float y, float z)
	{
		Vector3D v(x,y,z);
		return scale(v);
	}

	Matrix4D rotate(Vector3D& v, float angle)
	{
		return rotate(v.x(), v.y(), v.z(), angle);
	}

	Matrix4D rotate(float x, float y, float z, float angle)
	{
		// now the matrix is always correct
		// this formula worx only with normalized vector
		Vector3D v(x, y, z);
		v.normalize();
		float x = v.x();
		float y = v.y();
		float z = v.z();

		// book: Grundlagen der 3D-Programmierung, Gerhard Virag, S.495
		float c = cos(angle);
		float s = sin(angle);

		Matrix4D m;
		m.loadIdendity();

		// do the first row
		m.at_ref(0, 0) = x * x * (1 - c) + c;
		m.at_ref(0, 1) = x * y * (1 - c) - s * z;
		m.at_ref(0, 2) = x * z * (1 - c) + s * y;

		// do the second row
		m.at_ref(1, 0) = x * y * (1 - c) + s * z;
		m.at_ref(1, 1) = y * y * (1 - c) + c;
		m.at_ref(1, 2) = y * z * (1 - c) - x * s;

		// do the third row
		m.at_ref(2, 0) = x * z * (1 - c) - s * y;
		m.at_ref(2, 1) = y * z * (1 - c) + s * x;
		m.at_ref(2, 2) = z * z * (1 - c) + c;
	}

}
