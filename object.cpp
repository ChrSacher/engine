#include "object.h"

Physix::Object::Object()
{

}

void Physix::Object::advance(double dt)
{
	// new velocity
	__velocity+= __acceleration * dt;

	// new position
	__position+= __velocity * dt;

	// clear acceleration, because forces(and therefore acceleration) are calculated in each step
	// new
	__acceleration.reset();

}
