#include "Lighting.h"


AmbientLight::AmbientLight(Vector3 ambient)
{
	ambientLight=ambient;
}
AmbientLight::~AmbientLight(void)
{
};

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
}
SpotLight::SpotLight(PointLight point,Vector3 Dir,float Cutoff)
{
	pointLight = point;
	dir=Dir.normalize();
	cutoff=Cutoff;
}

Fog::Fog(float Density,Vector4 Color ,float Start ,float End,bool Type)
{
	density=Density;
	if(Start == End)
	{
		std::cout<<"Fog start = Fog end \nstart = start -1"<<std::endl;
		Start -= 1;
	}
	start=Start;
	end=End;
	color=Color;
	type=Type;
}
void Fog::setDensity(float Density)
{
	density=Density;
}
void Fog::setStart(float Start)
{
	if(Start == end)
	{
		std::cout<<"Fog start = Fog end \nstart = start -1"<<std::endl;
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

