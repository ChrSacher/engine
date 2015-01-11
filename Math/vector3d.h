#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "log.h"


namespace Physix
{

	/**
	 * @brief The Vector3D class implements a 3d vector for physical calculations
	 */
	class Vector3D
	{
	public:
		explicit Vector3D(double x, double y, double z) : __x{x}, __y{y}, __z{z} {}
		Vector3D() : Vector3D(0.0, 0.0, 0.0) {}

		/**
		 * @brief reset will zero __x, __y and __z
		 */
		void reset() { __x  = __y = __z = 0; }


		double x() const { return __x; }

		double y() const { return __y; }

		double z() const { return __z; }

		/**
		 * @brief operator * for multiplication with scalar
		 * @param scalar
		 * @return Scalar*vector like in math
		 */
		Vector3D operator*(double scalar) const;

		/**
		 * @brief operator += dont make a copy of this vector for this operation!
		 * @param right
		 * @return reference to this
		 */
		Vector3D& operator+=(const Vector3D& right);



	private:
		double __x = 0.0;
		double __y = 0.0;
		double __z = 0.0;

	};

	//Log& operator<<(Log& logger, const Vector3D& v);

}

#endif // VECTOR3D_H
