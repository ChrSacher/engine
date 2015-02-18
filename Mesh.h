#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "Vertex.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Math\vectors.h"

class Mesh
{

public:
	Mesh(void);
	Mesh(std::string path);
	~Mesh(void);

	GLuint vbo,size,ibo;
	void addVertex(Vertex newvertex);
	void addVertices(std::vector<Vertex> newvertices,std::vector<GLuint> indices);
	bool loadOBJ(std::string path);
	void loadBuffer();
    void clearData();
	void draw();
	std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<Vector3> normals;
	std::vector<Vertex> Vertices;
	std::vector<GLuint> vertexIndices,uvIndices,normalIndices;

};

