#include "Mesh.h"


Mesh::~Mesh(void)
{
	glDeleteVertexArrays(1,&vao);
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,Vertices.size());
	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices)
{
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	Vertices=vertices;
	loadBuffer();
}
Mesh::Mesh(std::string path)
{
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	loadOBJ(path);
}

Mesh::Mesh()
{
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	
}

Vertex::Vertex()
{
	pos=vec3(0,0,0);
}
Vertex::Vertex(const vec3& position,const vec2& tcoord)
{
	pos=position;
	uv=tcoord;
}
Vertex::Vertex(float x, float y, float z)
{
	pos=vec3(x,y,z);
}

void Mesh::loadOBJ(std::string path)
{
	printf("Loading OBJ file %s...\n", path.c_str());

	std::vector<vec3> temp_vertices; 
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;
	std::vector<GLuint> vertexIndices,uvIndices,normalIndices;


	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Impossible to open the file %s ",path.c_str());
		return ;
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
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			vec3 normal;
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
				printf("File %s cannot be read",path.c_str());
				return ;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1] );
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	for( unsigned int i=0; i<vertexIndices.size(); i++ )
	{
		glm::vec3 vertex = temp_vertices[ vertexIndices[i] - 1 ];
		glm::vec2 uv = temp_uvs[ uvIndices[i] - 1 ];
		Vertices.push_back(Vertex(vertex,uv));
	}
	loadBuffer();
	
};

void Mesh::loadBuffer()
{
	
	std::vector<vec3> positions;
	std::vector<vec2> uvs;
	positions.reserve(Vertices.size());
	uvs.reserve(Vertices.size());
	for(int i = 0;i< Vertices.size();i++)
	{
		positions.push_back(*Vertices[i].getPos());
		uvs.push_back(*Vertices[i].getUV());
	}
	glGenBuffers(NUMBUFFERS,vab);

	glBindBuffer(GL_ARRAY_BUFFER,vab[POSITIONVB]);
	glBufferData(GL_ARRAY_BUFFER,Vertices.size() * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	

	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREVB]);
	glBufferData(GL_ARRAY_BUFFER,Vertices.size() * sizeof(uvs[0]),&uvs[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindVertexArray(0);
}

void Mesh::clearData()
{
	Vertices.clear();
	Vertices.push_back(Vertex(vec3(0,0,0),vec2(0,0)));
	loadBuffer();
}