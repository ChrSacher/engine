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
       glDeleteFramebuffers(1, &m_fbo);
    }

    if (m_shadowMap != 0) 
	{
        glDeleteTextures(1, &m_shadowMap);
	}
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	width=WindowWidth;
	height=WindowHeight;
	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT,GL_FLOAT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) 
	{
		printf("FB error, status: 0x%x\n", Status);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return false;
	}
	lightDirection  = LightDirection;
	depthProjectionMatrix = Matrix4().identity().InitOrthographic(-30,30,-30,30,-300,600);
	depthViewMatrix = Matrix4().lookAt(lightDirection , Vector3(0,2,0), Vector3(0,1,0));
	depthModelMatrix = Matrix4(1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f);

	calculateMatrices();

	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true;
}

void ShadowMapFBO::BindForWriting()
{
	
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,m_shadowMap);
	
	glCullFace(GL_FRONT);
	glViewport(0,0,width,height);
	ShadowMapFBO::getShader()->use();
	glColorMask(false, false, false, false);
}

void ShadowMapFBO::BindForReading(GLuint unit)
{  
		
	ShadowMapFBO::getShader()->unuse();
	glCullFace(GL_BACK);
	glColorMask(TRUE,TRUE,TRUE,TRUE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D,m_shadowMap);
	BoundTexture::currentID = -1;
	BoundTexture::currentID = -1;
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
	ShadowMapFBO::getShader()->setUniform("depthMVP",depthMVP);

}

void ShadowMapFBO::setLightDirection(Vector3 LightDirection)
{
	lightDirection = LightDirection;
	depthViewMatrix = Matrix4().lookAt(lightDirection , Vector3(0,0,0), Vector3(0,1,0));
	calculateMatrices();
}

void ShadowMapFBO::addObject(Objekt &object)
{
	depthModelMatrix = object.transform.getMatrix();
	calculateMatrices();
	object.draw();
}