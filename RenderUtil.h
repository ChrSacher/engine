#pragma once
#include <string>
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>

class RenderUtil
{
public:
	RenderUtil(void);
	~RenderUtil(void);

	static void clearScreen();
	static void initGraphics();
	static std::string getOpenGLVersion();
};

