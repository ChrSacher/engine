#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"


std::map<std::string, Texture> TextureCache::_textureMap;


Texture::Texture(std::string path)
{
	addTexture(path);
}



void Texture::addTexture(std::string path)
{
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
	glGenTextures(1,&ID);
	glBindTexture(GL_TEXTURE_2D,ID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	stbi_image_free(data);
}


Texture::~Texture(void)
{

}

void Texture::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D,ID);
}

void Texture::unbind()
{
	//glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
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



Texture TextureCache::getTexture(std::string texturePath) 
{

    //lookup the texture and see if its in the map
    auto mit = _textureMap.find(texturePath);
    
    //check if its not in the map
    if (mit == _textureMap.end()) 
	{
        //Load the texture
		 Texture newTexture = TextureLoader::load(texturePath);
		 
        //Insert it into the map
		_textureMap.insert(make_pair(texturePath, newTexture));

        return newTexture;
    }
	printf("loaded cached Texture\n");
    return mit->second;
}

Texture TextureLoader::load(std::string filepath)
{
	Texture texture;
	int width,height,numComponents;
	printf("Loading texture %s\n",filepath.c_str());
	char* data = (char*)stbi_load(filepath.c_str(),&width,&height,&numComponents,4);
	texture.texturepath=filepath.c_str();
	if(data ==NULL)
	{
		printf("Couldn't load texture %s\nLoading Backup Texture\n",filepath.c_str());
		data = (char*)stbi_load("texture/white.png",&width,&height,&numComponents,4);
		texture.texturepath="Texture/white.png";
		if(data == NULL)
		{
			printf("Couldn't load backup texture");
			fatalError("Was not able to load basic texture");
		}
	}
	glGenTextures(1, &texture.ID);
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	glBindTexture(GL_TEXTURE_2D, 0);
	texture.width=width;
	texture.height=height;
	stbi_image_free(data);
	return texture;
}

