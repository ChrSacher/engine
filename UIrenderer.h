#pragma once
#include "Math/Vectors.h"
#include "Shader.h"
#include "Texture.h"
class Button
{
public:
	Button(Vector2 start,Vector2 size,Vector3 Color,bool Render);
	Vector2 start;
	Vector2 size;
	Vector2 rot;
	Vector3 color;
	Texture *texture;
	GLuint vao;
	bool render;

	enum
	{
		POSITIONVB,
		TEXTUREVB,
		NUMBUFFERS
	};
	GLuint vab[NUMBUFFERS];
	void loadBuffer();
};
class UIrenderer
{
public:
	UIrenderer();
	Shader *shader;
	std::vector<Button> buttons;
	void addButton(Button& newbutton){buttons.push_back(newbutton);};
	void draw();
	Matrix4 ortho;
};





