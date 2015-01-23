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

		float w() const = delete;
		void w(float w) = delete;

		Vector3D crossProduct(const Vector3D& v);
	};

	/**
	 * @brief scalarProduct between two vector3d
	 * @param v1
	 * @param v2
	 * @return scalarProduct
	 */
	float scalarProduct(const Vector3D& v1, const Vector3D& v2);

	/**
	 * @brief crossProduct between two vector3d
	 * @param v1
	 * @param v2
	 * @return crossProduct
	 */
	Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2);

}

#endif // VECTOR3D_H
