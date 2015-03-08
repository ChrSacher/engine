#pragma once
#include <map>


#include <string>
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <algorithm>
#include <iostream>
#include "Errors.h"
class Texture
{
public:
	Texture(std::string path = "Texture/white.png");
	Texture(const Texture &other);
	
	virtual ~Texture(void);
	void bind(int unit = 0);
	void unbind();
	GLuint texture;
	std::string texturepath;
	void drawTexture(bool check);
	void addTexture(std::string path);
};


