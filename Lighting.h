#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Math/Matrices.h"
#include "Math/Vectors.h"
#include "Errors.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

class AmbientLight
{
public:
	AmbientLight(Vector3 ambient,const Shader &rshader);
	~AmbientLight(void);

	Shader shader;
	Vector3 ambientLight;
	void setAmbient(Vector3 newambient);
	Vector3 getAmbient();
	void update();
};

class BaseLight
{
public:
	BaseLight(Vector3 Color = Vector3(0.3,0.4,0.1),float Intensity = 1.0f){color=Color;intensity=Intensity;}
	Vector3 color;
	float intensity;

	//setters
	void setColor(Vector3 Color){color=Color;};
	void setIntensity(float Intensity){intensity=Intensity;};
	//getters
	Vector3 getColor(){return color;};
	float getIntensity(){return intensity;};
};

class DirectionalLight
{
public:
	BaseLight base;
	Vector3 direction;
	
	DirectionalLight(BaseLight Base,Vector3 Dir,const Shader &rshader){base=Base;direction=Dir;shader=rshader;}
	void setBase(BaseLight Base){base=Base;};
	void setDirection(Vector3 dir){direction=dir;}
	BaseLight getBaseLight(){return base;};
	Vector3 getDirection(){return direction;};
	Shader shader;
	void update();
};