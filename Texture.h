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
	static void deleteCache();

private:
    static std::map<std::string, Texture> _textureMap;
};


class TextureLoader
{
	public:
	static Texture load(std::string filepath);
};

class CubemapTexture
{
public:

    CubemapTexture(const std::string& Directory,
        const std::string& PosXFilename,
        const std::string& NegXFilename,
        const std::string& PosYFilename,
        const std::string& NegYFilename,
        const std::string& PosZFilename,
        const std::string& NegZFilename);

	~CubemapTexture(){};
	CubemapTexture(){}
    bool Load();

    void bind(GLenum TextureUnit);
	void unbind();
	void addFiles(std::string a_sDirectory, std::string a_sFront, std::string a_sBack, std::string a_sLeft, std::string a_sRight, std::string a_sTop, std::string a_sBottom);
private:

    std::string fileNames[6];
    GLuint textureObj;
	
	
};