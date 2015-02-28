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
#include "Texture.h"
#include "Transform.h"
#include "Camera3d.h"
#include "RenderUtil.h"
#include <math.h>
#include "Material.h"

class Objekt
{
public:
	Objekt(std::string objektpath,Vector3 pos,Vector3 rot,std::string texturepath,Vector3 color);
	void operator=(const Objekt &other){};
	~Objekt(void);
	void draw();
	Material material;
	Mesh mesh;
	Transform transform;
};

