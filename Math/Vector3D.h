#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Vector4D.h"

namespace Math
{
	class Vector3D : public Vector4D
	{
	public:
		Vector3D() : Vector4D() {}
		Vector3D(float x, float y, float z) : Vector4D(x, y, z) {}

		Vector3D& crossProduct(const Vector3D& v);
	};

}

#endif // VECTOR3D_H
