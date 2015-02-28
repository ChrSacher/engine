#include "Objekt.h"


Objekt::Objekt(std::string objektpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color)
{
	material = Material(texturepath,color,2,32);
	transform.setPos(pos);
	transform.setRot(rot);
	mesh.loadOBJ(objektpath);
	transform.setScale(Vector3(1,1,1));
}


Objekt::~Objekt(void)
{
}

void Objekt::draw()
{
	
};