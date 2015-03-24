#include "Objekt.h"


Objekt::Objekt(std::string objektpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color)
{
	material = new Material(texturepath,color,2,32);
	transform = Transform(pos,rot,Vector3(1,1,1));
	mesh = Mesh(objektpath);
}


Objekt::~Objekt(void)
{

}

void Objekt::draw()
{
	mesh.draw();
};