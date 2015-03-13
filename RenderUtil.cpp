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
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnableClientState(GL_VERTEX_ARRAY);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_POINT_SMOOTH);	// Antialiasing für Punkte einschalten
	glEnable (GL_LINE_SMOOTH);	// Antialiasing für Linien einschalten
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_FRAMEBUFFER_SRGB);
}

std::string RenderUtil::getOpenGLVersion()
{
	return "ok";
}

void unbindTextures()
{
	glBindTexture(GL_TEXTURE_2D,0);
}