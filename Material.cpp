#include "Material.h"


Material::Material(std::string path,Vector3 Color,float intensity ,float power)
{
	
	texture.addTexture(path);
	color=Color;
	specularIntensity=intensity;
	specularPower= power;
}


Material::~Material(void)
{

}
