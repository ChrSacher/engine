#include "Shadow.h"


ShadowMapFBO::ShadowMapFBO()
{
	m_fbo = 0;
    m_shadowMap = 0;
}

ShadowMapFBO::~ShadowMapFBO()
{
	if (m_fbo != 0) 
	{
       glDeleteFramebuffers(1, &m_fbo);
    }

    if (m_shadowMap != 0) 
	{
        glDeleteTextures(1, &m_shadowMap);
	}
}
bool ShadowMapFBO::Init(unsigned int WindowWidth, unsigned int WindowHeight,Vector3 LightDirection)
{
	if (m_fbo != 0) 
	{
       glDeleteFramebuffersEXT(1, &m_fbo);
    }

    if (m_shadowMap != 0) 
	{
        glDeleteTextures(1, &m_shadowMap);
	}
	width=WindowWidth;
	height=WindowHeight;
	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, m_shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) 
	{
		printf("FB error, status: 0x%x\n", Status);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}
	lightDirection  = LightDirection;
	calculateMatrices();

	glClear(GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void ShadowMapFBO::BindForWriting()
{
	
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,width,height);
	ShadowMapFBO::getShader()->use();
	ShadowMapFBO::getShader()->setUniform("depthMVP",depthMVP);
	glColorMask(false, false, false, false);
}

void ShadowMapFBO::BindForReading(GLuint unit)
{  
	glColorMask(TRUE,TRUE,TRUE,TRUE);
	ShadowMapFBO::getShader()->unuse();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
	glActiveTexture(GL_TEXTURE0 + unit);
	//glBindTexture(GL_TEXTURE_2D,m_shadowMap);
}

Shader* ShadowMapFBO::getShader()
{
	static Shader *shader = NULL;
	if(!shader)
	{
		shader = new Shader();
		shader->addVertexShader("Shaders/shadowShader.vert");
		shader->addFragmentShader( "Shaders/shadowShader.frag");
		shader->addAttribute("position");
		shader->addAttribute("uv");
		shader->addAttribute("normal");
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
	depthProjectionMatrix = Matrix4().identity().InitOrthographic(-10,10,-10,10,-10,20);
	depthViewMatrix = Matrix4().lookAt(lightDirection , Vector3(0,0,0), Vector3(0,1,0));
	depthModelMatrix = Matrix4(1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f);
	depthMVP =  (depthProjectionMatrix * depthViewMatrix *  depthModelMatrix);
}

void ShadowMapFBO::setLightDirection(Vector3 LightDirection)
{
	lightDirection = LightDirection;
	calculateMatrices();
}