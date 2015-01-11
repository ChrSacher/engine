#ifndef OBJECT_H
#define OBJECT_H

#include "vector3d.h"
#include "log.h"


namespace Physix
{

	class Object
	{
	public:
		Object();

		/**
		 * @brief accelerate this object in a direction and with an value
		 * @param acc
		 */
		void accelerate(const Vector3D& acc) { __acceleration+= acc; }

		/**
		 * @brief advance will calculate the next position/velocity with forward euler
		 * @param dt how much time passed since last call
		 */
		void update(double dt);

		Vector3D position() const { return __position; }

		Vector3D velocity() const { return __velocity; }

		Vector3D acceleration() const { return __acceleration; }


	private:
		Vector3D __position;	/** in m */
		Vector3D __velocity;	/** in m/s */
		Vector3D __acceleration;/** in m/(s**2) */
	};

}

/**
 * @brief operator << for debugging purpose
 * @param log
 * @param o
 * @return logger for chaining
 */
//Log& operator<<(Log& log, const Physix::Object& o);

#endif // OBJECT_H
