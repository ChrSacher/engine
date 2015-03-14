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
	glGenBuffers(NUMBUFFERS,vab);
}

void UIrenderer::draw()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->use();
	shader->setUniform("ortho",ortho);
	int offset = 0;
	for(int i=0;i < buttons.size();i++)
	{
		if(buttons[i].render)
		{
			shader->setUniform("baseColor",buttons[i].color);
			buttons[i].texture.bind();
			glBindVertexArray(vao);
			glDrawArrays(GL_QUADS,offset,4);		
			glBindVertexArray(0);
			offset += 4;
			buttons[i].texture.unbind();
		}
	}
	shader->unuse();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

Button::Button(Vector2 Start,Vector2 Size,Vector4 Color,bool Render,std::string texturepath)
{
	start=Start;
	size=Size;
	color = Color;
	render=Render;
	ID=IDCounter;
	texture = TextureCache::getTexture(texturepath);
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
		if(buttons[i].render)
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
	}
	

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

void UIrenderer::updateOrtho(float width,float height)
{
	ortho = Matrix4().identity().InitOrthographic(0,width,0,height,-1,1);
}

void Skybox::loadSkybox(std::string Directory, std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz) 
{ 
	cube.addFiles(Directory,  posx, negx,  posy,  negy, posz, negz);
	cube.Load();
   glGenVertexArrays(1, &vao); 
   glBindVertexArray(vao); 

   Mesh *mesh = new Mesh("Models/box.obj");
   
	if(mesh->model.Vertices.size() != 0)
	{
		std::vector<Vector3> positions;
		for(int i = 0;i< mesh->model.Vertices.size();i++)
		{
			positions.push_back(*mesh->model.Vertices[i].getPos() * 2);
		}
	
		glGenBuffers(1, &vbo);


		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glBufferData(GL_ARRAY_BUFFER,mesh->model.Vertices.size() * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
		glBindVertexArray(0);
		delete(mesh);
		transform.setScale(Vector3(200,200,200));
	}
}

Skybox::Skybox(Vector4 Color)
{
	shader = new Shader();
	shader->addVertexShader("Shaders/Skybox.vert");
	shader->addFragmentShader( "Shaders/Skybox.frag");
	shader->addAttribute("position");
	shader->bind();
	shader->linkShaders();
	color = Color;
}

void Skybox::renderSkybox()
{
	glDepthMask(0);
	glCullFace(GL_FRONT);
	glBindVertexArray(vao);
	shader->use();
	shader->setUniform("WVP", camera->GetViewProjection() * transform.getMatrix() );
	shader->setbaseColor(color);
	cube.bind(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	shader->unuse();
	cube.unbind();
	glDepthMask(1);
	glCullFace(GL_BACK);
	glBindVertexArray(0);
}

void Skybox::releaseSkybox()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1,&vbo);
	delete(shader);
}

void UIrenderer::releaseRenderer()
{
	glDeleteVertexArrays(1, &vao);
	for(int i =0;i<NUMBUFFERS;i++)
	{
		glDeleteBuffers(1,&vab[i]);
	}
	delete(shader);
}