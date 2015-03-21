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


