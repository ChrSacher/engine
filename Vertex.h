#pragma once

#include "Math/Vectors.h"
#include <iostream>


static int VERTEXSIZE = 3;
class Vertex
{
public:
	Vertex(void);
	Vertex(Vector3 newpos);
	Vertex(Vector3 newposn,Vector2 newuv,Vector3 newnormal);

	~Vertex(void);

	//setters
	void setPos(Vector3 newpos);
	void setPos(float x,float y, float z);

	Vector3 getpos();

	Vector3 pos;
};

