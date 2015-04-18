#include "Object.h"

GLuint Object::id = 0;
Object::Object(std::string Objectpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color,bool autoCenter)
{

	ID = id;
	id++;
	material = new Material(texturepath,color,2,32);
	transform =  new Transform(pos,rot,Vector3(1,1,1));
	mesh = new Mesh(Objectpath,autoCenter);
	renderable = true;
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
	ID = id;
	id++;
	material = new Material();
	transform = new Transform();
	mesh = new Mesh();
	renderable = true;
}

Object::Object(const Object& otherobject)
{
	ID = id;
	id++;
	material = new Material(*otherobject.material);
	transform = new Transform(*otherobject.transform);
	mesh = new Mesh(*otherobject.mesh);
	renderable = true;
}

bool Object::operator==(const Object& other)
{
	return (ID && other.ID);
}

