#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"


Texture::Texture(const std::string path)
{
	int width,height,numComponents;
	char* data = (char*)stbi_load(path.c_str(),&width,&height,&numComponents,4);
	if(data ==NULL)
	{
		printf("Couldn't load texture %s\n",path.c_str());
	}
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	stbi_image_free(data);

}


Texture::~Texture(void)
{
	glDeleteTextures(1,&texture);
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit<= 31);
	glActiveTexture(GL_TEXTURE0 + unit); //not sure if needed
	glBindTexture(GL_TEXTURE_2D,texture);
}

void Texture::drawTexture(bool check)
{
	if(check == 0)
	{
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
	}
}