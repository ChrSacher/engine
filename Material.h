#pragma once
#include "Texture.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "Math/3DMath.h"

 
class Material
{
public:
	Material(std::string,Vector3 Color = Vector3(1,1,1),float intensity = 2,float exponent = 32);
	Material(){}
	~Material(void);

	Texture texture;
	Vector3 color;

	float specularIntensity;
	float specularPower;

	float getIntensity(){return specularIntensity;}
	float getPower(){return specularPower;}

	void setIntensity(float inten){specularIntensity=inten;}
	void setPower(float power){specularPower=power;}

	void set(Texture &rtexture,Vector3 rcolor,float rintensity,float rpower){texture=rtexture;color=rcolor;specularIntensity=rintensity;specularPower=rpower;}
	Material& getMaterial(){return *this;};
};

