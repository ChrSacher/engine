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

void Transform::calculateMatrix()
{
	modelMatrix = Matrix4().identity().translate(pos).scale(sca).rotateX(rot.x).rotateY(rot.y).rotateZ(rot.z);
}

void Transform::setPos(Vector3& Pos)
{
	pos = Pos;
	update=true;
}
void Transform::setRot(Vector3& Rot)
{
	rot=Rot;
	update=true;
}
void Transform::setScale(Vector3& Scale)
{
	sca = Scale;
	update=true;
}