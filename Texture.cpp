#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"


std::map<std::string, TextureAndCount> TextureCache::textureMap;


Texture::Texture(std::string path)
{
	*this = TextureCache::getTexture(path);
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
	if(unit < 0 || unit > 30) fatalError("Texture unit is too large/too low");
	BoundTexture::getInstance().bind(ID,unit);
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
    auto mit = textureMap.find(texturePath);
    
    //check if its not in the map
    if (mit == textureMap.end()) 
	{
        //Load the texture
		 Texture newTexture = TextureLoader::load(texturePath);
		 
        //Insert it into the map
		textureMap.insert(make_pair(texturePath, TextureAndCount(newTexture,1)));

        return newTexture;
    }
	printf("loaded cached Texture\n");
	mit->second.count ++;
    return mit->second.texture;
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
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2); //anisotropy filtering for better quality but more workload
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	glBindTexture(GL_TEXTURE_2D, 0);
	texture.width=width;
	texture.height=height;
	stbi_image_free(data);

	
	return texture;
}


void TextureCache::lowerCount(std::string texturePath)
{
	auto mit = textureMap.find(texturePath);
    
    //check if its not in the map
    if (mit == textureMap.end()) 
	{
        printf("Cannot lower count on non existing texture path %s\n",texturePath);
		return;
    }
	mit->second.count --;
	if(mit->second.count < 1)
	{
		mit->second.texture.releaseTexture();
		textureMap.erase(mit);
	}
	return;
}

void TextureCache::lowerCount(GLuint textureID)
{
	for (std::map<std::string,TextureAndCount>::iterator mit = textureMap.begin(); mit != textureMap.end(); ++mit)
	{
		if(mit->second.texture.ID == textureID)
		{
			mit->second.count -- ;
			if(mit->second.count < 1)
			{
				mit->second.texture.releaseTexture();
				textureMap.erase(mit);
			}
			return;
		};
	};
	printf("couldn't find ID %d",textureID);
}



bool CubemapTexture::Load()
{
	if(ID > 0.1) glDeleteTextures(1,&ID);
    glGenTextures(1, &ID);
	glActiveTexture (GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	GLenum types[6];
	types[0] = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	types[1] = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	types[2] = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	types[3] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	types[4] = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	types[5] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

    for (unsigned int i = 0 ; i < 6 ; i++) 
	{
		int width,height,numComponents;
		printf("loading CubeMapTexture %s\n",fileNames[i].c_str());
		char* data = (char*)stbi_load(fileNames[i].c_str(),&width,&height,&numComponents,4);
        if(data ==NULL)
		{
			printf("Couldn't load Cube Texture %s\n",fileNames[i].c_str());
			data = (char*)stbi_load("texture/white.png",&width,&height,&numComponents,4);
			if(data == NULL)
			{
				printf("Couldn't load backup texture\n");
				fatalError("Was not able to load basic texture\n");
				return false;
			}
		}

		glTexImage2D(types[i], 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
    } 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



    return true;
}

void CubemapTexture::bind(GLuint unit)
{
	if(unit < 0 || unit > 32)
	{
			fatalError("Texture unit is too large/too low");
			return;
	}
	BoundTexture::getInstance().bind(ID,unit,GL_TEXTURE_CUBE_MAP);
}

void CubemapTexture::addFiles(std::string Directory, std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz)
{
	fileNames[0] = Directory + posx;
	fileNames[1] = Directory + negx;
	fileNames[2] = Directory +  posy;
	fileNames[3] = Directory +  negy;
	fileNames[4] = Directory +  posz;
	fileNames[5] = Directory +  negz;
}

CubemapTexture::CubemapTexture(const std::string& Directory, const std::string& PosXFilename, const std::string& NegXFilename,
							   const std::string& PosYFilename, const std::string& NegYFilename,  const std::string& PosZFilename, const std::string& NegZFilename)

{
	addFiles(Directory,PosXFilename,NegXFilename,PosYFilename,NegYFilename,PosZFilename, NegZFilename);
	Load();
}
void CubemapTexture::releaseCubemap()
{
	BoundTexture::getInstance().unbind(ID);
	glDeleteTextures(1,&ID);
}


void TextureCache::deleteCache()
{
	for (std::map<std::string,TextureAndCount>::iterator it = textureMap.begin(); it != textureMap.end(); ++it)
	{
		it->second.texture.releaseTexture();
	}	
}


void Texture::releaseTexture()
{
	BoundTexture::getInstance().unbind(ID);
	glDeleteTextures(1,&ID);
}

bool BoundTexture::isBound(GLuint ID,GLuint unit)
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM,&program);
	auto mit = boundUnitMap.find(program);
	if (mit == boundUnitMap.end()) 
	{
		GLuint newarray[31] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
		std::vector<GLuint> temp(newarray,newarray + 31);
		boundUnitMap.insert(std::make_pair((GLuint)program,temp));
		return false;
    }
	if(mit->second[unit] == ID)
	{		
		return true;
	}
	else return false;
	
}

void BoundTexture::unbind(GLuint ID,GLenum TextureType)
{
	for (auto mit = boundUnitMap.begin(); mit != boundUnitMap.end(); ++mit)
	{
		for(int i = 0; i < 31 ; i++)
		{
			if(mit->second[i] == ID)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(TextureType,0);
			}
		}
	}
}

void BoundTexture::bind(GLuint ID,GLuint unit,GLenum TextureType)
{
		if(!(isBound(ID,unit)))
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(TextureType, ID);
			GLint program;
			glGetIntegerv(GL_CURRENT_PROGRAM,&program);
			auto mit = boundUnitMap.find(program);
			if (mit == boundUnitMap.end()) 
			{
				printf("BoundTexture unexpected error which shouldn't happen \n");
				return;
			}
			mit->second[unit] = ID;
		}

}

BoundTexture& BoundTexture::getInstance()
{
	static BoundTexture boundTexture;
	return boundTexture;
}