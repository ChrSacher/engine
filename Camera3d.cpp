#include "Camera3d.h"
const float DEG2RAD = 3.141593f / 180;

Camera3d::Camera3d(Vector3 Pos,float fov,float aspect,float zNear,float zFar)
{
	perspectiveMatrix=Matrix4().perspective(fov,aspect,zNear,zFar);
	transform = Transform(Pos,Vector3(0,0,0),Vector3(1,1,1));
	cameraspeed=0.5;
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

}
void Camera3d::movebackward(float distance )
{

}
void Camera3d::raise(float distance )
{

}
void Camera3d::sink(float distance )
{

}
void Camera3d::turnright(float distance )
{

}
void Camera3d::turnleft(float distance )
{

}

void Camera3d::strafeleft(float distance )
{

}
void Camera3d::straferight(float distance )
{

}

Vector3 Camera3d::getDir()
{
	return Vector3(0,0,0);
}