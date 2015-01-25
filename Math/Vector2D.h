#ifndef VECTOR2D_H
#define VECTOR2D_H


#include "Vector3D.h"

namespace Math
{
	class Vector2D : public Vector3D
	{
	public:
		Vector2D() : Vector3D(0, 0, 0) {}
		Vector2D(float x, float y) : Vector3D(x, y, 0) {}

		void z(float z) = delete;
		float z() const = delete;
	};

	/**
	 * @brief scalarProduct between two vector2d
	 * @param v1
	 * @param v2
	 * @return scalarProduct
	 */
	float scalarProduct(const Vector2D& v1, const Vector2D& v2);
}

#endif // VECTOR2D_H
