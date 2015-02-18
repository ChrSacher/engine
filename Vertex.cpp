#include "Vertex.h"


Vertex::Vertex(void)
{
	pos = Vector3(0,0,0);
}

Vertex::Vertex(Vector3 newpos)
{
	pos = newpos;
}

Vertex::~Vertex(void)
{

}

void Vertex::setPos(Vector3 newpos)
{
	pos = newpos;
}
void Vertex::setPos(float x,float y, float z)
{
	pos = Vector3(x,y,z);
}

Vector3 Vertex::getpos()
{
	return pos;
}
