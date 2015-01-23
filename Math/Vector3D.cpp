#include "Vector3D.h"

namespace Math
{

	Vector3D Vector3D::crossProduct(const Vector3D& v)
	{
		Vector3D r;

		r.x(y() * v.z() - z() * v.y());
		r.y(z() * v.x() - x() * v.z());
		r.z(x() * v.y() - y() * v.x());

		return r;
	}

	float scalarProduct(const Vector3D& v1, const Vector3D& v2)
	{
		return v1.x() * v2.x() + v1.y() * v1.y() + v1.z() * v1.z();
	}

	Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2)
	{
		Vector3D r;

		r.x(v1.y() * v2.z() - v1.z() * v2.y());
		r.y(v1.z() * v2.x() - v1.x() * v2.z());
		r.z(v1.x() * v2.y() - v1.y() * v2.x());

		return r;
	}

}
