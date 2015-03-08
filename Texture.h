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
#include <vector>
class Texture
{
public:
	Texture(){}
	Texture(std::string path );
	
	virtual ~Texture(void);
	void bind(int unit = 0);
	void unbind();
	GLuint ID;
	int width,height;
	std::string texturepath;
	void drawTexture(bool check);
	void addTexture(std::string path);
};

class TextureCache
{
public:

    static Texture getTexture(std::string texturePath);

private:
    static std::map<std::string, Texture> _textureMap;
};


class TextureLoader
{
	public:
	static Texture load(std::string filepath);
};