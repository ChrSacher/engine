#include "Matrix3D.h"
#include <stdexcept>
#include <iostream>

namespace Math
{
	Matrix3D::Matrix3D()
	{
		for(auto i = 0; i < 3; i++)
			for(auto j = 0; j < 3; j++)
				data[i][j] = 0;
	}

	void Matrix3D::loadIdendity()
	{
		for(auto i = 0; i < 3; i++)
			data[i][i] = 1;
	}

	void Matrix3D::setRow(int nbr, Vector3D& row)
	{
		if(nbr < 0 || nbr >= 3)
			throw std::out_of_range("Range for Matrix3D is: 0 <= x <= 3!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 3; i++)
			data[nbr][i] = row[i];
	}

	void Matrix3D::setColumn(int nbr, Vector3D& col)
	{
		if(nbr < 0 || nbr >= 3)
			throw std::out_of_range("Range for Matrix3D is: 0 <= x <= 3!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 3; i++)
			data[i][nbr] = col[i];
	}

	Vector3D Matrix3D::getRow(int nbr)
	{
		if(nbr < 0 || nbr >= 3)
			throw std::out_of_range("Range for Matrix3D is: 0 <= x <= 3!");

		Vector3D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 3; i++)
			v[i] = data[nbr][i];

		return v;
	}

	Vector3D Matrix3D::getColumn(int nbr)
	{
		if(nbr < 0 || nbr >= 3)
			throw std::out_of_range("Range for Matrix3D is: 0 <= x <= 3!");

		Vector3D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 3; i++)
			v[i] = data[i][nbr];

		return v;
	}

	float Matrix3D::at(int row, int col) const
	{
		if(row < 0 || row >= 3 || col < 0 || col >= 3)
			throw std::out_of_range("Range for Matrix3D is: 0 <= x <= 3!");

		return data[row][col];
	}

	float&Matrix3D::at_ref(int row, int col)
	{
		if(row < 0 || row >= 3 || col < 0 || col >= 3)
			throw std::out_of_range("Range for Matrix3D is: 0 <= x <= 3!");

		return data[row][col];
	}

	Matrix3D&Matrix3D::operator+(const Matrix3D& m)
	{
		for(auto i = 0; i < 3; i++)
			for(auto j = 0; j < 3; j++)
				data[i][j]+= m.data[i][j];

		return *this;
	}

	Matrix3D&Matrix3D::operator-(const Matrix3D& m)
	{
		for(auto i = 0; i < 3; i++)
			for(auto j = 0; j < 3; j++)
				data[i][j]-= m.data[i][j];

		return *this;
	}

	Vector3D&Matrix3D::operator[](int i)
	{
		if(i < 0 || i >= 3)
			throw std::out_of_range("Matrix3D has four Dimensions.");

		return data[i];
	}

	const Vector3D&Matrix3D::operator[](int i) const
	{
		if(i < 0 || i >= 3)
			throw std::out_of_range("Matrix3D has four Dimensions.");

		return data[i];
	}

	void Matrix3D::print() const
	{
		for(auto i = 0; i < 3; i++)
		{
			for(auto j = 0; j < 3; j++)
			{
				std::cout << data[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}
}
