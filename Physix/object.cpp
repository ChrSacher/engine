#include "object.h"

Physix::Object::Object()
{
}


void Physix::Object::update(double dt)
{
	// new velocity
	__velocity+= __acceleration * dt;

	// new position
	__position+= __velocity * dt;

	// clear acceleration, because forces(and therefore acceleration) are calculated in each step
	// new
	__acceleration.reset();

}


/*Log& operator<<(Log& log, const Physix::Object& o)
{
	log << o.acceleration() << "\n";
	log << o.velocity() << "\n";
	log << o.position() << "\n";
}*/
