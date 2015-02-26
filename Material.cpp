#include "Material.h"


Material::Material(std::string path,Vector3 Color)
{
	
	texture = new Texture(path);
	color=Color;

}


Material::~Material(void)
{

}
