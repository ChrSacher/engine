#include "Objekt.h"


Objekt::Objekt(std::string objektpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color,bool autoCenter)
{
	material = new Material(texturepath,color,2,32);
	transform =  new Transform(pos,rot,Vector3(1,1,1));
	mesh = new Mesh(objektpath,autoCenter);
}


Objekt::~Objekt(void)
{
	if(material || transform || mesh)
	{
		delete(material,transform,mesh);
	}
}

void Objekt::draw()
{
	mesh->draw();
};

Matrix4& Objekt::getMatrix()
{
	return transform->getMatrix();
}

Objekt::Objekt()
{
	material = new Material();
	transform = new Transform();
	mesh = new Mesh();
}