#include "Objekt.h"


Objekt::Objekt(std::string objektpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color,Shader &rshader)
{
	material = Material(texturepath,color);
	transform.setPos(pos);
	transform.setRot(rot);
	mesh=Mesh(objektpath);
	
	shader=rshader;
	transform.setPos(Vector3(0,0,0));
}


Objekt::~Objekt(void)
{
}

void Objekt::draw()
{
	shader.setUniform("ambientLight",Vector3(1,1,1));
};