#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL\glew.h>
#include "Math/Vectors.h" 
#include "Math/Matrices.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"
#include <math.h>

#define PI 3.14159265358979323846f
 
class Camera3d
{
public:
    Camera3d(Vector3 Pos,float fov,float aspect,float zNear,float zFar);
	~Camera3d(void);
	Camera3d(){}
	Matrix4 perspectiveMatrix;
	Matrix4 viewMatrix;

	void set(Vector3 Pos,Vector3 Rot){transform.setPos(Pos);transform.setRot(Rot);};
	void setPos(Vector3 newpos){transform.setPos(newpos);};
	void setPos(float newx,float newy,float newz){transform.setPos(Vector3(newx,newy,newz));};
	
	void setRot(Vector3 newrot){transform.setRot(newrot);};
	void setRot(float newx,float newy,float newz){transform.setRot(Vector3(newx,newy,newz));};

	Vector3 getPos(){return transform.pos;};
	Vector3 getRot(){return transform.rot;};
	Vector3 getDir();
	Transform transform;
	float cameraspeed;
	bool updateneeded;

	Matrix4& GetViewProjection();
	void updatePerspectiveMatrix(float fov,float aspect,float zNear,float zFar);

	//movement
	void moveforward(float distance = 0);
	void movebackward(float distance = 0);
	void raise(float distance = 0);
	void sink(float distance = 0);
	void turnright(float distance = 0);
	void turnleft(float distance = 0);
	void strafeleft(float distance = 0);
	void straferight(float distance = 0);

};