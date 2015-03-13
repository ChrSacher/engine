#include "Transform.h"


Transform::Transform(const Vector3 &Pos,const Vector3 &Rot,const Vector3 &Scale)
{
	pos=Pos;
	rot=Rot;
	sca=Scale;
	calculateMatrix();
	
}


Transform::~Transform(void)
{
}

Matrix4 Transform::getMatrix() 
{
	if(pos != oldpos || sca != oldsca || rot != oldrot)
	{
		calculateMatrix();
		oldpos=pos;
		oldrot=rot;
		oldsca=sca;
	}
	return modelMatrix;
};

void Transform::calculateMatrix()
{
	modelMatrix = Matrix4().identity().scale(sca).translate(pos).rotateX(rot.x).rotateY(rot.y).rotateZ(rot.z);
}

void Transform::setPos(Vector3& Pos)
{
	pos = Pos;
}
void Transform::setRot(Vector3& Rot)
{
	rot=Rot;
}
void Transform::setScale(Vector3& Scale)
{
	sca = Scale;
}