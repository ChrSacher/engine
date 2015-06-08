#include "Lighting.h"

GLuint AmbientLight::ID = 0;
GLuint PointLight::ID = 0;
GLuint DirectionalLight::ID = 0;
GLuint SpotLight::ID = 0;
GLuint Fog::ID = 0;

AmbientLight::AmbientLight(Vector3 ambient)
{
	ambientLight=ambient;
	_ID = AmbientLight::ID++;
}
AmbientLight::~AmbientLight(void)
{

};
DirectionalLight::DirectionalLight(BaseLight Base ,Vector3 Dir)
{
	base=Base;direction=Dir;
	_ID = DirectionalLight::ID++;
}
void AmbientLight::setAmbient(Vector3 newambient)
{
	ambientLight=newambient;
};

Vector3 AmbientLight::getAmbient()
{
	return ambientLight;
};

PointLight::PointLight(Vector3 Pos,BaseLight Base,Attenuation Atten,float Range)
{
	pos=Pos;
	base=Base;
	attenuation=Atten;
	range=Range;
	_ID = PointLight::ID++;
}
SpotLight::SpotLight(PointLight point,Vector3 Dir,float Cutoff)
{
	pointLight = point;
	dir=Dir.normalize();
	cutoff=Cutoff;
	_ID = SpotLight::ID++;
}

Fog::Fog(float Density,Vector4 Color ,float Start ,float End,bool Type)
{
	density=Density;
	if(Start == End)
	{
		std::cout<<"Fog start = Fog end \nstart = start -= 1"<<std::endl;
		Start -= 1;
	}
	start=Start;
	end=End;
	color=Color;
	type=Type;
	_ID = Fog::ID++;
}
void Fog::setDensity(float Density)
{
	density=Density;
}
void Fog::setStart(float Start)
{
	if(Start == end)
	{
		std::cout<<"Fog start = Fog end \nstart = start -= 1"<<std::endl;
		Start -= 1;
	}
	start=Start;
}
void Fog::setEnd(float End)
{
	if(start == End)
	{
		std::cout<<"Fog start = Fog end \nend  = end + 1"<<std::endl;
		End += 1;
	}
	end=End;
}
void Fog::setColor(Vector4 Color)
{
	color=Color;
}
void Fog::setType(int Type)
{
	type=Type;
}

