#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"




Texture::Texture(std::string path)
{
	addTexture(path);
}



void Texture::addTexture(std::string path)
{
	glGenTextures(1,&texture);
	int width,height,numComponents;
	char* data = (char*)stbi_load(path.c_str(),&width,&height,&numComponents,4);
	texturepath=path.c_str();
	if(data ==NULL)
	{
		printf("Couldn't load texture %s\n Loading Backup Texture\n",path.c_str());
		data = (char*)stbi_load("texture/white.png",&width,&height,&numComponents,4);
		texturepath="Texture/white.png";
		if(data == NULL)
		{
			printf("Couldn't load backup texture");
			fatalError("Was not able to load basic texture");
		}
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

void Texture::bind()
{
	
	glBindTexture(GL_TEXTURE_2D,texture);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0) ;
}

void Texture::drawTexture(bool check)
{
	if(check)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{		
		glDisable(GL_TEXTURE_2D);
	}
}

