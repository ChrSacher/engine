#pragma once
#include <glm/glm.hpp>
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <vector>
using namespace glm;
class Vertex
{
public:
	Vertex();
	Vertex(const vec3& position,const vec2& tcoord);
	Vertex(float x,float y,float z);
	inline vec3* getPos(){return &pos;};
	inline vec2* getUV(){return &uv;};
	vec3 pos;
	vec2 uv;

};


class Mesh
{
public:
	Mesh(void);
	virtual ~Mesh(void);
	Mesh(std::vector<Vertex> vertices);
	Mesh(std::string path);
	std::vector<Vertex> Vertices;
	void draw();
	void loadOBJ(std::string path);
	void loadBuffer();
	void clearData();
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);
	enum
	{
		POSITIONVB,
		TEXTUREVB,
		NUMBUFFERS
	};
	GLuint vao,vbo;
	GLuint vab[NUMBUFFERS];
};
