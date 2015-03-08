#pragma once
#include "Math/Vectors.h"
#include "Shader.h"
#include "Texture.h"
class Button
{
public:
	Button(Vector2 start,Vector2 size,Vector4 Color,bool Render);
	Vector2 start;
	Vector2 size;
	Vector2 rot;
	Vector4 color;
	Texture *texture;
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
	GLuint vao;enum
	{
		POSITIONVB,
		TEXTUREVB,
		NUMBUFFERS
	};
	GLuint vab[NUMBUFFERS];
	void loadBuffer();

};





