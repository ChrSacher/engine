#include "Camera3d.h"
const float DEG2RAD = 3.141593f / 180;

Camera3d::Camera3d(Vector3 Pos,float fov,float aspect,float zNear,float zFar)
{
	perspectiveMatrix=Matrix4().perspective(fov,aspect,zNear,zFar);
	transform = Transform(Pos,Vector3(0,0,0),Vector3(1,1,1));
	cameraspeed=1;
}

Matrix4& Camera3d::GetViewProjection() 
{
	viewMatrix = perspectiveMatrix * transform.getMatrix();
	return viewMatrix;
}

Camera3d::~Camera3d(void)
{

}

void Camera3d::updatePerspectiveMatrix(float fov,float aspect,float zNear,float zFar)
{
	perspectiveMatrix=Matrix4().identity().perspective(fov,aspect,zNear,zFar);
}

void Camera3d::moveforward(float distance)
{
	if(distance==0)
	{
		transform.setPos(transform.getPos() + Vector3(sin(transform.rot[1] * DEG2RAD) * cameraspeed,0,-cos(transform.rot[1] * DEG2RAD) * cameraspeed));
	}
	else
	{
		transform.setPos(transform.getPos() + Vector3(sin(transform.rot[1] * DEG2RAD) * distance,0,-cos(transform.rot[1] * DEG2RAD) * distance));
	}
}
void Camera3d::movebackward(float distance )
{
	if(distance==0)
	{
		transform.setPos(transform.getPos() - Vector3(sin(transform.rot[1] * DEG2RAD) * cameraspeed,0,-cos(transform.rot[1] * DEG2RAD) * cameraspeed));
	}
	else
	{
		transform.setPos(transform.getPos() - Vector3(sin(transform.rot[1] * DEG2RAD) * distance,0,-cos(transform.rot[1] * DEG2RAD) * distance));
	}
}
void Camera3d::raise(float distance )
{
	if(distance==0)
	{
		setPos(Vector3(getPos()[0],getPos()[1] - cameraspeed,getPos()[2]));
	}
	else
	{
		setPos(Vector3(getPos()[0],getPos()[1] - distance,getPos()[2]));
	}
}
void Camera3d::sink(float distance )
{
	if(distance==0)
	{
		setPos(Vector3(getPos()[0],getPos()[1] + cameraspeed,getPos()[2]));
	}
	else
	{
		setPos(Vector3(getPos()[0],getPos()[1] + distance,getPos()[2]));
	}

}
void Camera3d::turnright(float distance )
{
	if(distance==0)
	{
		setRot(Vector3(getRot()[0],getRot()[1] - cameraspeed * 4,getRot()[2]));
	}
	else
	{
		setRot(Vector3(getRot()[0],getRot()[1] - distance,getRot()[2]));
	}
}
void Camera3d::turnleft(float distance )
{
	if(distance==0)
	{
		setRot(Vector3(getRot()[0],getRot()[1] + cameraspeed * 4,getRot()[2]));
	}
	else
	{
		setRot(Vector3(getRot()[0],getRot()[1] + distance,getRot()[2]));
	}
}

void Camera3d::strafeleft(float distance )
{
	if(distance==0)
	{

	}
	else
	{

	}
}
void Camera3d::straferight(float distance )
{
	if(distance==0)
	{

	}
	else
	{

	}
}

Vector3 Camera3d::getDir()
{


	return Vector3(0,0,0);
}