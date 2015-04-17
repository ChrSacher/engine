#pragma once
#include "Math/3DMath.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <vector>
#include <map>
#include <string>
 


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
	Vector3& getPos(){return pos;};
	Vector2& getUV(){return uv;};
	Vector3& getNormal(){return normal;};
	Vector3 pos;
	Vector2 uv;
	Vector3 normal;
};

struct Model
{
	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> uvs;
	std::vector<GLuint> Indices;
	std::vector<Vertex> Vertices;
	OBJIndex index;
	void center();
};

class OBJLoader
{
public:

	static Model loadOBJ(std::string path,bool autoCenter = false);
};




class Mesh
{
public:
	Mesh(void);
	virtual ~Mesh(void);
	Mesh(std::vector<Vertex> vertices);
	Mesh(std::string path,bool autoCenter = false);
	void init();
	void draw();
	void loadOBJ(std::string path,bool autoCenter = false);
	void loadBuffer();
	void loadBufferVertex();
	void clearData();
	Model model;
	void releaseMesh();
private:
	bool indiced;
	
	enum
	{
		POSITIONVB,
		TEXTUREVB,
		NORMALVB,
		INDICESVB,
		NUMBUFFERS
	};
	
	GLuint vao ,vab[NUMBUFFERS];
};


class ModelCache
{
public:

    static Model getModel(std::string modelPath,bool autoCenter = false);
	static void deleteCache();

private:
    static std::map<std::string, Model> _modelMap;
};


