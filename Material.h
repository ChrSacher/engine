#pragma once
#include "Texture.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "stb_image.h"
#include "Math/Matrices.h" #include "Math/Vectors.h"

 
class Material
{
public:
	Material(std::string = "",Vector3 Color = Vector3(1,1,1));
	~Material(void);

	Texture *texture;
	Vector3 color;
};

