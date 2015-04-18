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
#include "Math/3DMath.h"
#include "Errors.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera3d.h"
#include <math.h>
#include "Material.h"

class Object
{
public:
	Object(std::string Objectpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color,bool autoCenter = false);
	Object(const Object& otherobject);
	Object();
	~Object(void);
	void draw();
	Matrix4& getMatrix();
	GLuint ID;
	Material *material;
	Mesh *mesh;
	Transform *transform;
	bool operator=(const Object& other);
	bool renderable;
private:
	static GLuint id;
};

