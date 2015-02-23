#pragma once



#include <string>
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "stb_image.h"
#include <iostream>
class Texture
{
public:
	Texture(const std::string path);
	virtual ~Texture(void);
	Texture(const Texture& other){};
	Texture& operator=(const Texture& other){};
	void bind(unsigned int unit);
	GLuint texture;
	void drawTexture(bool check);
};

