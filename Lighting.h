#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Math/Matrices.h"
#include "Math/Vectors.h"
#include "Errors.h"
#include "Mesh.h"
#include "Transform.h"

class ShadowMapFBO //funktioniert irgentwie nicht 
{
    public:
        ShadowMapFBO();

        ~ShadowMapFBO();

        bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

        void BindForWriting();

        void BindForReading(GLenum TextureUnit);
		Matrix4 biasMatrix;
        GLuint m_fbo;
        GLuint m_shadowMap;
};

class AmbientLight
{
public:
	AmbientLight(Vector3 ambient = Vector3(0.1,0.1,0.1));
	~AmbientLight(void);

	Vector3 ambientLight;
	void setAmbient(Vector3 newambient);
	Vector3 getAmbient();
};

class BaseLight
{
public:
	BaseLight(Vector3 Color = Vector3(0.3,0.4,0.1),float Intensity = 1.0f){color=Color;intensity=Intensity;}
	Vector3 color;
	float intensity;
	//setters
	void setColor(Vector3 Color){color=Color;};
	void setIntensity(float Intensity){intensity=Intensity;};
	//getters
	Vector3 getColor(){return color;};
	float getIntensity(){return intensity;};
};

class DirectionalLight
{
public:
	BaseLight base;
	Vector3 direction;
	
	DirectionalLight(BaseLight Base,Vector3 Dir){base=Base;direction=Dir;}
	void setBase(BaseLight Base){base=Base;};
	void setDirection(Vector3 dir){direction=dir;}
	BaseLight getBaseLight(){return base;};
	Vector3 getDirection(){return direction;};
};

class Attenuation
{
	public:
		Attenuation(float Constant = 0,float Linear = 0,float Exponent = 1){constant=Constant;linear=Linear;exponent=Exponent;}
		~Attenuation(void){};
		float constant;
		float linear;
		float exponent;

		void setConstant(float newconstant){constant=newconstant;};
		void setLinear(float newlinear){linear=newlinear;};
		void setExponent(float newexponent){exponent=newexponent;}

		float getConstant(){return constant;};
		float getLinear(){return linear;};
		float getExponent(){return exponent;};

};

class PointLight
{
public:
	PointLight(Vector3 Pos = Vector3(0,0,0),BaseLight Base = BaseLight(),Attenuation Atten = Attenuation(),float Range = 0);
	Vector3 pos;
	float range;
	BaseLight base;
	Attenuation attenuation;


};

class SpotLight
{
public:
	PointLight pointLight;
	Vector3 dir;
	float cutoff;
	SpotLight(PointLight point,Vector3 Dir,float Cutoff);
	~SpotLight(){};
	//setters
	void setPointLight(PointLight &light){pointLight=light;}
	void setDir(Vector3 Dir){dir=Dir;}
	void setCutOff(float Cutoff){cutoff=Cutoff;}
	//getters
	PointLight& getPointLight(){return pointLight;}
	Vector3& getDir(){return dir;}
	float& getcutoff(){return cutoff;}
};

class Fog
{
public:
	Fog(float Density,Vector4 Color = Vector4(0.5,0.5,0.5,1),float Start = 0,float End = 0,bool Type = true){density=Density;start=Start;end=End;color=Color;type=Type;}
	float density; //exp fog
	float start; //linear fog only
	float end; //linear fog only
	Vector4 color;
	int type; //0 = fog disabled 1 = linear 2 = exp 

	void setDensity(float Density){density=Density;}
	void setStart(float Start){if(Start != end)start=Start;else fatalError("Fog start = Fog end");}
	void setEnd(float End){if(End != start)end=End;else fatalError("Fog start = Fog end");}
	void setColor(Vector4 Color){color=Color;}
	void setType(int Type){type=Type;}
};