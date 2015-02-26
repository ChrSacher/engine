#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL\glew.h>
#include "Math/Vectors.h" 
#include "Math/Matrices.h"
#include <glm/gtc/matrix_transform.hpp>
 
class Camera3d
{
public:
    Camera3d(Vector3 Pos,float fov,float aspect,float zNear,float zFar);
	~Camera3d(void);
	Matrix4 perspectiveMatrix;
	Matrix4 viewMatrix;

	Vector3 pos,dir,up;
	float cameraspeed;
	bool updateneeded;

	Matrix4 GetViewProjection();
	void updatePerspectiveMatrix(float fov,float aspect,float zNear,float zFar);
	void moveforward();
	void movebackward();
	void turnright();
	void turnleft();
	void straferight();
	void strafeleft();
	void lookup();
	void lookdown();


};