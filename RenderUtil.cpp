#include "RenderUtil.h"


RenderUtil::RenderUtil(void)
{
}


RenderUtil::~RenderUtil(void)
{
}

void RenderUtil::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
}
void RenderUtil::initGraphics()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

std::string RenderUtil::getOpenGLVersion()
{
	return "ok";
}

void unbindTextures()
{
	glBindTexture(GL_TEXTURE_2D,0);
}