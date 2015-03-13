#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "Math/Vectors.h"
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

};	
class UIrenderer
{
public:
	UIrenderer();
	Shader *shader;
	std::vector<Button> buttons;
	void addButton(Button& newbutton){buttons.push_back(newbutton);loadBuffer();};
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
   void loadSkybox(std::string a_sDirectory, std::string a_sFront, std::string a_sBack, std::string a_sLeft, std::string a_sRight, std::string a_sTop, std::string a_sBottom); 
   void renderSkybox(); 
   Skybox(Vector4 Color = Vector4(1,1,1,1));
   ~Skybox(){};
   void setCamera(Camera3d* Camera){camera=Camera;};
   void releaseSkybox(); 
   void setColor(Vector4 Color){color=Color;}
   void setPos(Vector3 Pos){transform.setPos(Pos);};
   void setRot(Vector3 Rot){transform.setRot(Rot);}
   void setScale(Vector3 Scale){transform.setPos(Scale);}
private: 
	Shader* shader;
	Camera3d *camera;
	GLuint vao,vbo;
	CubemapTexture cube;
	Transform transform;
	Vector4 color;
};





