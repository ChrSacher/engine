#include "Shadow.h"


ShadowMapFBO::ShadowMapFBO(unsigned int ShadowWidth, unsigned int ShadowHeight,unsigned int WindowWidth, unsigned int WindowHeight,Vector3 LightDirection,bool enabled)
{
	isEnabled = enabled;
	glGenFramebuffersEXT(1, &m_fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	shadowWidth=ShadowWidth;
	shadowHeight=ShadowHeight;
	windowWidth=WindowWidth;
	windowHeight=WindowHeight;
	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, m_shadowMap, 0);
	 glBindTexture(GL_TEXTURE_2D, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	GLenum Status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (Status != GL_FRAMEBUFFER_COMPLETE_EXT) 
	{
		printf("FB error, status: 0x%x\n", Status);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		isEnabled = false;
		return;
	}
	lightDirection  = LightDirection;

	depthProjectionMatrix = Matrix4().identity().InitOrthographic(-10,10,-10,10,-10,10);

	depthViewMatrix = Matrix4().lookAt(lightDirection,Vector3(0,0,0), Vector3(0,1,0));

	depthModelMatrix = Matrix4().identity();

	biasMatrix = Matrix4(	0.5, 0.0, 0.0, 0.0,
							0.0, 0.5, 0.0, 0.0,
							0.0, 0.0, 0.5, 0.0,
							0.5, 0.5, 0.5, 1.0
							);
	calculateMatrices();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return;
}

ShadowMapFBO::~ShadowMapFBO()
{
       glDeleteFramebuffers(1, &m_fbo);
       glDeleteTextures(1, &m_shadowMap);
}


void ShadowMapFBO::BindForWriting()
{
	if(isEnabled)
	{
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, m_fbo);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glCullFace(GL_FRONT);
		glBindTexture(GL_TEXTURE_2D,m_shadowMap);
		glViewport(0,0,shadowWidth,shadowHeight);
		ShadowMapFBO::getShader()->use();
		ShadowMapFBO::getShader()->setUniform("depthMVP",depthMVP);
		glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	}
}

void ShadowMapFBO::BindForReading(GLuint unit)
{  
	if(isEnabled)
	{	
		ShadowMapFBO::getShader()->unuse();
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
		depthMVP = Matrix4().identity();
		glCullFace(GL_BACK);
		calculateMatrices();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0,0,windowWidth,windowHeight);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D,m_shadowMap);
		BoundTexture::currentID = -1;
		BoundTexture::currentID = -1;
	}
}

Shader* ShadowMapFBO::getShader()
{
	static Shader *shader = NULL;
	if(!shader)
	{
		shader = new Shader();
		shader->addVertexShader("Shaders/shadowShader.vert");
		shader->addFragmentShader( "Shaders/shadowShader.frag");
		shader->bind();
		shader->linkShaders();
		return shader;
	} 
	else
		return shader;
}

void ShadowMapFBO::deleteShader()
{
	delete(getShader());
}

void ShadowMapFBO::calculateMatrices()
{
	depthMVP =  depthProjectionMatrix * depthViewMatrix *  depthModelMatrix;
}

void ShadowMapFBO::setLightDirection(Vector3 LightDirection)
{
	lightDirection = LightDirection;
	depthViewMatrix = Matrix4().lookAt(lightDirection , Vector3(0,0,0), Vector3(0,1,0));
	calculateMatrices();
}

void ShadowMapFBO::addObject(Objekt *object)
{
	if(isEnabled)
	{
		depthModelMatrix = object->getMatrix();
		calculateMatrices();
		ShadowMapFBO::getShader()->setUniform("depthMVP",depthMVP);
		object->draw();
	}
}