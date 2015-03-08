#include "UIrenderer.h"

int Button::IDCounter = 0;
UIrenderer::UIrenderer()
{
	shader = new Shader();
	shader->addVertexShader("Shaders/2DShader.vert");
	shader->addFragmentShader( "Shaders/2DShader.frag");
	shader->addAttribute("position");
	shader->addAttribute("uv");
	shader->bind();
	shader->linkShaders();
	ortho= Matrix4().identity().InitOrthographic(0,640,0,480,-1,1);
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
}

void UIrenderer::draw()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->use();
	shader->setUniform("ortho",ortho);

	for(int i=0;i < buttons.size();i++)
	{
		shader->setUniform("baseColor",buttons[i].color);
		glBindVertexArray(vao);
		glDrawArrays(GL_QUADS,0,buttons.size() * 4);		
		glBindVertexArray(0);
	}
	shader->unuse();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

Button::Button(Vector2 Start,Vector2 Size,Vector4 Color,bool Render)
{
	start=Start;
	size=Size;
	color = Color;
	render=Render;
	ID=IDCounter;
	Button::IDCounter++;
	
}
void UIrenderer::loadBuffer()
{
	std::vector<Vector2> positions;
	std::vector<Vector2> uvs;
	positions.reserve(buttons.size() * 4);
	uvs.reserve(buttons.size() * 4);
	for(int i=0;i< buttons.size();i++)
	{
	positions.push_back(buttons[i].start);
	positions.push_back(Vector2(buttons[i].start.x + buttons[i].size.x,buttons[i].start.y));
	positions.push_back(Vector2(buttons[i].start.x + buttons[i].size.x,buttons[i].start.y + buttons[i].size.y));
	positions.push_back(Vector2(buttons[i].start.x ,buttons[i].start.y + buttons[i].size.y));

	uvs.push_back(Vector2(0,0));
	uvs.push_back(Vector2(1,0));
	uvs.push_back(Vector2(1,1));
	uvs.push_back(Vector2(0,1));
	}
	glGenBuffers(NUMBUFFERS,vab);

	glBindBuffer(GL_ARRAY_BUFFER,vab[POSITIONVB]);
	glBufferData(GL_ARRAY_BUFFER,buttons.size() * 4 * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);

	
	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREVB]);
	glBufferData(GL_ARRAY_BUFFER,buttons.size() * 4 * sizeof(uvs[0]),&uvs[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindVertexArray(0);
}
