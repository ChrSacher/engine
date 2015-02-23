#include "Transform.h"


Transform::Transform(const vec3 &Pos,const vec3 &Rot,const vec3 &Scale)
{
	pos=Pos;
	rot=Rot;
	sca=Scale;
}


Transform::~Transform(void)
{
}

void Transform::calculateMatrix()
{
	mat4 posMatrix = translate(pos);
	mat4 rotXMatrix = rotate(rot[0],vec3(1,0,0));
	mat4 rotYMatrix = rotate(rot[0],vec3(0,1,0));
	mat4 rotZMatrix = rotate(rot[0],vec3(0,0,1));
	mat4 scaleMatrix = scale(sca);
	mat4 rotationMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
	modelMatrix = scaleMatrix * rotationMatrix * posMatrix;

}