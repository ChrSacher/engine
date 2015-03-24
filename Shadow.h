#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <string>
#include "Errors.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Math/3DMath.h"
#include "Shader.h"
#include "Objekt.h"
class ShadowMapFBO //funktioniert irgentwie nicht 
{
    public:
        ShadowMapFBO();

		~ShadowMapFBO();

        bool Init(unsigned int WindowWidth, unsigned int WindowHeight,Vector3 LightDirection);

        void BindForWriting();
        void BindForReading(GLuint unit = 0);
		
		Matrix4 biasMatrix, depthProjectionMatrix, depthViewMatrix,depthModelMatrix,depthMVP;
        GLuint m_fbo;
        GLuint m_shadowMap;
		Vector3 lightDirection;
		void calculateMatrices();
		void setLightDirection(Vector3 LightDirection);
		void addObject(Objekt &object);
		int width,height;
		static void deleteShader();
private:
		static Shader * getShader();
		
		
};
