#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "Math/3DMath.h"
#include "Shader.h"
#include "Texture.h"
class Button
{
public:
	Button(Vector2 start,Vector2 size,Vector4 Color,bool Render,std::string texturepath);
	Vector2 start;
	Vector2 size;
	Vector2 rot;
	Vector4 color;
	Texture texture;
	int ID;
	static int IDCounter;
	bool render;
	bool operator<(Button &other);
};	
class UIrenderer
{
public:
	UIrenderer();
	~UIrenderer();
	Shader *shader;
	std::vector<Button> buttons;
	void addButton(Button& newbutton);
	void addButton(Vector2 Start,Vector2 Size,Vector4 Color,bool Render,std::string texturepath);
	void draw();
	Matrix4 ortho;
	void updateOrtho(float width,float height);
	GLuint vao;enum
	{
		POSITIONVB,
		TEXTUREVB,
		NUMBUFFERS
	};
	GLuint vab[NUMBUFFERS];
	void loadBuffer();
};

class Skybox 
{ 
public: 
   void loadSkybox(std::string Directory, std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz); 
   void setSkyboxTexture(std::string Directory, std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz); 
   void renderSkybox(); 
   Skybox(Camera3d &Camera = Camera3d(),Vector4 Color = Vector4(1,1,1,1));
   ~Skybox();
   void setCamera(Camera3d* Camera);
   void setColor(Vector4 Color);
   void setPos(Vector3 Pos);
   void setRot(Vector3 Rot);
   void setScale(Vector3 Scale);
private: 
	Shader* shader;
	Camera3d *camera;
	GLuint vao,vbo;
	CubemapTexture cube;
	Transform transform;
	Vector4 color;
};





