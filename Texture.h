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

class BoundTexture
{
public:
	static BoundTexture& getInstance();
	

	BoundTexture(BoundTexture const&);              // Don't Implement
	void operator=(BoundTexture const&);

	std::map<GLuint,std::vector<GLuint>> boundUnitMap; //Shader, Bound textures map  //unit 31 is reserviert für schatten
	bool isBound(GLuint ID,GLuint unit);
	void unbind(GLuint ID,GLenum TextureType = GL_TEXTURE_2D);
	void bind(GLuint ID,GLuint unit,GLenum TextureType = GL_TEXTURE_2D);

private:
	BoundTexture(){};
	~BoundTexture(){};
};


class Texture
{
public:
	Texture(){ID = 0;}
	Texture(std::string path);
	
	virtual ~Texture(void);
	void bind(int unit = 0);
	GLuint ID;
	int width,height;
	std::string texturepath;
	void drawTexture(bool check);
	void addTexture(std::string path);
	void releaseTexture();
};

struct TextureAndCount
{
	Texture texture;
	GLuint count;
	TextureAndCount(Texture newtexture,GLuint Count){count = Count;texture = newtexture;};
};

class TextureCache
{
public:

    static Texture getTexture(std::string texturePath);
	static void lowerCount(std::string texturePath);
	static void lowerCount(GLuint textureID);
	static void deleteCache();
	
private:
    static std::map<std::string, TextureAndCount> textureMap;
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
    void bind(GLuint unit = 0);
	void addFiles(std::string Directory, std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz);
	void releaseCubemap();
private:

    std::string fileNames[6];
    GLuint ID;
	
	
};