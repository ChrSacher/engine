#ifndef OBJECT_H
#define OBJECT_H

#include "vector3d.h"


namespace Physix
{

	class Object
	{
	public:
		Object();

		/**
		 * @brief advance will calculate the next position/velocity with forward euler
		 * @param dt how much time passed since last call
		 */
		void advance(double dt);


	private:
		Vector3D __position;
		Vector3D __velocity;
		Vector3D __acceleration;
	};

}

#endif // OBJECT_H
