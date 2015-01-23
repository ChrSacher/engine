#include "Vector4D.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace Math
{

	float Vector4D::length() const
	{
		float sum = 0;

		for(auto i = 0; i < 3; i++)
			sum+= data[i] * data[i];

		return sqrt(sum);
	}

	Vector4D&Vector4D::normalize()
	{
		float l = this->length();
		for(auto i = 0; i < 3; i++)
			data[i]/= l;

		return *this;
	}

	Vector4D Vector4D::getNormalized() const
	{
		Vector4D v(*this);

		return v.normalize();
	}

	Vector4D& Vector4D::add(const Vector4D& v)
	{
		data[0] += v.data[0];
		data[1] += v.data[1];
		data[2] += v.data[2];
		data[3] += v.data[3];

		return *this;
	}

	Vector4D& Vector4D::subtract(const Vector4D& v)
	{
		data[0] -= v.data[0];
		data[1] -= v.data[1];
		data[2] -= v.data[2];
		data[3] -= v.data[3];

		return *this;
	}

	float Vector4D::scalarProduct(const Vector4D& v)
	{
		return data[0] * v.x() + data[1] * v.y() + data[2] * v.z() + data[3] * v.w();
	}

	void Vector4D::print() const
	{
		std::cout << "[";

		for(auto i = 0; i < 4; i++)
			std::cout << data[i] << ";";
		std::cout << "]" << std::endl;
	}

	float Vector4D::operator[](int index) const
	{
		if(index < 0 || index >= 4)
			throw std::out_of_range("0 <= x <= 3 is the range of vector4d");

		return data[index];
	}

	float& Vector4D::operator[](int index)
	{
		if(index < 0 || index >= 4)
			throw std::out_of_range("0 <= x <= 3 is the range of vector4d");

		return data[index];
	}



	Vector4D operator+(const Vector4D& v, const Vector4D& w)
	{
		Vector4D res(v);

		return res.add(w);
	}

	Vector4D operator-(const Vector4D& v, const Vector4D& w)
	{
		Vector4D res(v);

		return res.subtract(w);
	}

	float scalarProduct(const Vector4D& v1, const Vector4D& v2)
	{
		return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w();
	}
}
