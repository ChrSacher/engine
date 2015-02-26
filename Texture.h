#pragma once
#include <map>


#include <string>
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "stb_image.h"
#include <iostream>
#include "Errors.h"
class Texture
{
public:
	Texture(const std::string path);
	Texture();
	virtual ~Texture(void);
	Texture(const Texture& other){};
	void bind();
	void unbind();
	GLuint texture;
	void drawTexture(bool check);
	void addTexture(std::string path);
	Texture &operator=(Texture other);
};


