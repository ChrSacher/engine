#include "Camera3d.h"


Camera3d::Camera3d(Vector3 Pos,float fov,float aspect,float zNear,float zFar)
{
	perspectiveMatrix=Matrix4().perspective(fov,aspect,zNear,zFar);
	pos=Pos;
	dir = Vector3(0,0,1);
	up = Vector3(0,1,0);
	cameraspeed=0.5;
	updateneeded=true;
}

Matrix4 Camera3d::GetViewProjection() 
{
	if(updateneeded)
	{
			updateneeded=false;
			viewMatrix = perspectiveMatrix * Matrix4().identity().translate(pos);
	};
	return viewMatrix;
}

Camera3d::~Camera3d(void)
{

}

void Camera3d::updatePerspectiveMatrix(float fov,float aspect,float zNear,float zFar)
{
	perspectiveMatrix=Matrix4().identity().perspective(fov,aspect,zNear,zFar);
}

void Camera3d::moveforward()
{
	
}
void Camera3d::movebackward()
{
	
}
void Camera3d::turnright()
{
	
}
void Camera3d::turnleft()
{
	
}
void Camera3d::straferight()
{
	
}
void Camera3d::strafeleft()
{
	
}

void Camera3d::lookup()
{

}
void Camera3d::lookdown()
{

}