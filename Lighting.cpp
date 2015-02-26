#include "Lighting.h"


AmbientLight::AmbientLight(Vector3 ambient,const Shader &rshader)
{
	ambientLight=ambient;
	shader=rshader;
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

void AmbientLight::update()
{
	shader.setUniform("ambientLight",ambientLight);
}

void DirectionalLight::update()
{
		shader.setUniform("directionalLight.direction",direction);
		shader.setUniform("directionalLight.base.color",base.color);
		shader.setUniform("directionalLight.base.intensity",base.intensity);
}