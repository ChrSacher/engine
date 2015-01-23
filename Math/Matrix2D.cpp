#include "Matrix2D.h"
#include <stdexcept>
#include <iostream>

namespace Math
{
	Matrix2D::Matrix2D()
	{
		for(auto i = 0; i < 1; i++)
			for(auto j = 0; j < 1; j++)
				data[i][j] = 0;
	}

	void Matrix2D::loadIdendity()
	{
		for(auto i = 0; i < 1; i++)
			data[i][i] = 1;
	}

	void Matrix2D::setRow(int nbr, Vector2D& row)
	{
		if(nbr < 0 || nbr >= 1)
			throw std::out_of_range("Range for Matrix2D is: 0 <= x <= 1!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 1; i++)
			data[nbr][i] = row[i];
	}

	void Matrix2D::setColumn(int nbr, Vector2D& col)
	{
		if(nbr < 0 || nbr >= 1)
			throw std::out_of_range("Range for Matrix2D is: 0 <= x <= 1!");

		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 1; i++)
			data[i][nbr] = col[i];
	}

	Vector2D Matrix2D::getRow(int nbr)
	{
		if(nbr < 0 || nbr >= 1)
			throw std::out_of_range("Range for Matrix2D is: 0 <= x <= 1!");

		Vector2D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 1; i++)
			v[i] = data[nbr][i];

		return v;
	}

	Vector2D Matrix2D::getColumn(int nbr)
	{
		if(nbr < 0 || nbr >= 1)
			throw std::out_of_range("Range for Matrix2D is: 0 <= x <= 1!");

		Vector2D v;
		// for definition of interpreation see comment in class declaration
		for(auto i = 0; i < 1; i++)
			v[i] = data[i][nbr];

		return v;
	}

	float Matrix2D::at(int row, int col) const
	{
		if(row < 0 || row >= 1 || col < 0 || col >= 1)
			throw std::out_of_range("Range for Matrix2D is: 0 <= x <= 1!");

		return data[row][col];
	}

	float&Matrix2D::at_ref(int row, int col)
	{
		if(row < 0 || row >= 1 || col < 0 || col >= 1)
			throw std::out_of_range("Range for Matrix2D is: 0 <= x <= 1!");

		return data[row][col];
	}

	Matrix2D&Matrix2D::operator+(const Matrix2D& m)
	{
		for(auto i = 0; i < 1; i++)
			for(auto j = 0; j < 1; j++)
				data[i][j]+= m.data[i][j];

		return *this;
	}

	Matrix2D&Matrix2D::operator-(const Matrix2D& m)
	{
		for(auto i = 0; i < 1; i++)
			for(auto j = 0; j < 1; j++)
				data[i][j]-= m.data[i][j];

		return *this;
	}

	Vector2D&Matrix2D::operator[](int i)
	{
		if(i < 0 || i >= 4)
			throw std::out_of_range("Matrix2D has two Dimensions.");

		return data[i];
	}

	const Vector2D&Matrix2D::operator[](int i) const
	{
		if(i < 0 || i >= 1)
			throw std::out_of_range("Matrix2D has two Dimensions.");

		return data[i];
	}

	void Matrix2D::print() const
	{
		for(auto i = 0; i < 1; i++)
		{
			for(auto j = 0; j < 1; j++)
			{
				std::cout << data[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}
}
