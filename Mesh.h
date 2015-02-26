#pragma once
#include "Math/Vectors.h" 
#include "Math/Matrices.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <vector>

 


struct OBJIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;
    
    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class Vertex
{
public:
	Vertex();
	Vertex(const Vector3& position,const Vector2& tcoord,const Vector3 &tnormal);
	Vertex(float x,float y,float z);
	inline Vector3* getPos(){return &pos;};
	inline Vector2* getUV(){return &uv;};
	inline Vector3* getNormal(){return &normal;};
	Vector3 pos;
	Vector2 uv;
	Vector3 normal;
};

struct Model
{
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector2> uvs;
	std::vector<GLuint> Indices;
	std::vector<Vertex> Vertices;
	OBJIndex index;
	Model();

};

static class OBJLoader
{
public:
	OBJLoader(void);
	~OBJLoader(void);

	static Model loadOBJ(std::string path);
};




class Mesh
{
public:
	Mesh(void);
	virtual ~Mesh(void);
	Mesh(std::vector<Vertex> vertices);
	Mesh(std::string path);
	
	void draw();
	void loadOBJ(std::string path);
	void loadBuffer();
	void loadBufferVertex();
	void clearData();
	Model model;
	void operator=(const Mesh& other){};
private:
	bool indiced;
	Mesh(const Mesh& other);
	
	enum
	{
		POSITIONVB,
		TEXTUREVB,
		NORMALVB,
		INDICESVB,
		NUMBUFFERS
	};
	
	GLuint vao,vbo;
	GLuint vab[NUMBUFFERS];
};


