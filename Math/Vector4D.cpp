#include "Vector4D.h"

namespace Math
{

	Vector4D& Vector4D::operator+(const Vector4D& v)
	{
		data[0] += v.data[0];
		data[1] += v.data[1];
		data[2] += v.data[2];
		data[3] += v.data[3];

		return *this;
	}

	Vector4D& Vector4D::operator-(const Vector4D& v)
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


}
