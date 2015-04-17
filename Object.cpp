#include "Object.h"


Object::Object(std::string Objectpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color,bool autoCenter)
{
	static GLuint id = 0;
	id++;
	ID = id;
	material = new Material(texturepath,color,2,32);
	transform =  new Transform(pos,rot,Vector3(1,1,1));
	mesh = new Mesh(Objectpath,autoCenter);
}


Object::~Object(void)
{
	if(material || transform || mesh)
	{
		delete(material,transform,mesh);
	}
}

void Object::draw()
{
	mesh->draw();
};

Matrix4& Object::getMatrix()
{
	return transform->getMatrix();
}

Object::Object()
{
	material = new Material();
	transform = new Transform();
	mesh = new Mesh();
}

Object::Object(const Object& otherobject)
{
	material = new Material(*otherobject.material);
	transform = new Transform(*otherobject.transform);
	mesh = new Mesh(*otherobject.mesh);
}

bool Object::operator=(const Object& other)
{
	return (ID && other.ID);
}

