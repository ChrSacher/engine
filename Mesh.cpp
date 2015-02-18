#include "Mesh.h"


Mesh::Mesh(void)
{
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&ibo);
	size=0;
}

Mesh::Mesh(std::string path)
{
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&ibo);
	size=0;
	loadOBJ(path);
}


Mesh::~Mesh(void)
{

}
void Mesh::addVertex(Vertex newvertex)
{
	size += VERTEXSIZE;
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(newvertex),&newvertex,GL_STATIC_DRAW);
}

void Mesh::addVertices(std::vector<Vertex> newvertices,std::vector<GLuint> indices)
{
	size += indices.size();
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,newvertices.size() * sizeof(Vertex),&newvertices[0],GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),&indices[0],GL_STATIC_DRAW);
}

void Mesh::draw()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glVertexAttribPointer(0,3,GL_FLOAT,false,VERTEXSIZE * 4,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
	glDrawElements(GL_TRIANGLES,size,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(0);
}

bool Mesh::loadOBJ(std::string path)
{
	printf("Loading OBJ file %s...\n", path.c_str());

	std::vector<Vector3> temp_vertices; 
	std::vector<Vector2> temp_uvs;
	std::vector<Vector3> temp_normals;
	GLuint currentvert,currentuv,currentnormal;
	currentvert = vertices.size();
	currentuv = uvs.size();
	currentnormal = normals.size();


	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return false;
	}

	while( 1 )
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			Vector2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			std::string vertex1, vertex2, vertex3;
			GLuint vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9)
			{
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0] - 1 + currentvert);
			vertexIndices.push_back(vertexIndex[1] - 1 + currentvert);
			vertexIndices.push_back(vertexIndex[2] - 1 + currentvert);
			uvIndices    .push_back(uvIndex[0] - 1 + currentuv);
			uvIndices    .push_back(uvIndex[1] - 1 + currentuv);
			uvIndices    .push_back(uvIndex[2] - 1 + currentuv);
			normalIndices.push_back(normalIndex[0] - 1 + currentnormal);
			normalIndices.push_back(normalIndex[1] - 1 + currentnormal);
			normalIndices.push_back(normalIndex[2] - 1 + currentnormal);
		}else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( GLubyte i=0; i<temp_vertices.size(); i++ )
	{
		vertices.push_back( temp_vertices[ i ]);
	}
	for( GLubyte i=0; i<temp_uvs.size(); i++ )
	{
		uvs     .push_back(temp_uvs[i]);
	}
	for( GLubyte i=0; i<temp_normals.size(); i++ )
	{
		normals .push_back(temp_normals[i]);
	}
	for(int i=0;i<vertices.size();i++)
	{
		Vertices.push_back(Vertex(vertices[i]));
	}
	return true;

}
 