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

}
