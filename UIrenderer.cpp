#include "UIrenderer.h"

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
		shader->setbaseColor(buttons[i].color);
		glBindVertexArray(buttons[i].vao);
		glDrawArrays(GL_QUADS,0,4);		
		glBindVertexArray(0);
	}
	shader->unuse();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

Button::Button(Vector2 Start,Vector2 Size,Vector3 Color,bool Render)
{
	start=Start;
	size=Size;
	color = Color;
	render=Render;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	loadBuffer();
}
void Button::loadBuffer()
{
	std::vector<Vector2> positions;
	std::vector<Vector2> uvs;
	positions.reserve(4);
	uvs.reserve(4);

	positions.push_back(start);
	positions.push_back(Vector2(start.x + size.x,start.y));
	positions.push_back(Vector2(start.x + size.x,start.y + size.y));
	positions.push_back(Vector2(start.x ,start.y + size.y));

	uvs.push_back(Vector2(0,0));
	uvs.push_back(Vector2(1,0));
	uvs.push_back(Vector2(1,1));
	uvs.push_back(Vector2(0,1));

	glGenBuffers(NUMBUFFERS,vab);

	glBindBuffer(GL_ARRAY_BUFFER,vab[POSITIONVB]);
	glBufferData(GL_ARRAY_BUFFER,4 * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);

	
	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREVB]);
	glBufferData(GL_ARRAY_BUFFER,4 * sizeof(uvs[0]),&uvs[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindVertexArray(0);
}
