#include "Objekt.h"


Objekt::Objekt(std::string objektpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color)
{
	material = new Material(texturepath,color,2,32);
	transform = new Transform(pos,rot,Vector3(1,1,1));
	mesh = new Mesh(objektpath);
}


Objekt::~Objekt(void)
{
	delete(material,transform,mesh);
}

void Objekt::draw()
{
	
};