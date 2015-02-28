#include "Mesh.h"

Model loadOBJ(std::string path);

Mesh::~Mesh(void)
{
	glDeleteVertexArrays(1,&vao);
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	if(!indiced)
	{
		glDrawArrays(GL_TRIANGLES,0,model.Vertices.size());		
	}
	else
	{	
		glDrawElementsBaseVertex(GL_TRIANGLES,model.Indices.size(),GL_UNSIGNED_INT,0,0);
	}
	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices)
{
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	for(int i=0;i<vertices.size();i++)
	{
		model.Vertices.push_back(vertices[i]);
	}
	loadBufferVertex();
}
Mesh::Mesh(std::string path)
{
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	loadOBJ(path);
	loadBufferVertex();
	
}

Mesh::Mesh()
{
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	
}

Vertex::Vertex()
{
	pos=Vector3(0,0,0);
}
Vertex::Vertex(const Vector3& position,const Vector2& tcoord,const Vector3 &tnormal)
{
	pos=position;
	uv=tcoord;
	normal = tnormal;
}
Vertex::Vertex(float x, float y, float z)
{
	pos=Vector3(x,y,z);
}

void Mesh::loadOBJ(std::string path)
{
	model = OBJLoader::loadOBJ(path);
	loadBufferVertex();
	
};

void Mesh::loadBufferVertex()
{
	indiced=false;
	if(model.Vertices.size() != 0)
	{
	std::vector<Vector3> positions;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	positions.reserve(model.Vertices.size());
	uvs.reserve(model.Vertices.size());
	normals.reserve(model.Vertices.size());
	for(int i = 0;i< model.Vertices.size();i++)
	{
		positions.push_back(*model.Vertices[i].getPos());
		uvs.push_back(*model.Vertices[i].getUV());
		normals.push_back(*model.Vertices[i].getNormal());
	}
	glGenBuffers(NUMBUFFERS,vab);

	glBindBuffer(GL_ARRAY_BUFFER,vab[POSITIONVB]);
	glBufferData(GL_ARRAY_BUFFER,model.Vertices.size() * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	
	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREVB]);
	glBufferData(GL_ARRAY_BUFFER,model.Vertices.size() * sizeof(uvs[0]),&uvs[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALVB]);
	glBufferData(GL_ARRAY_BUFFER,model.Vertices.size() * sizeof(normals[0]),&normals[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);
	glBindVertexArray(0);
	}
}

void Mesh::clearData()
{
	model.Vertices.clear();
}

void Mesh::loadBuffer()
{
	indiced=true;
	glGenBuffers(NUMBUFFERS,vab);

	glBindBuffer(GL_ARRAY_BUFFER,vab[POSITIONVB]);
	glBufferData(GL_ARRAY_BUFFER,model.vertices.size() * sizeof(model.vertices[0]),&model.vertices[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	
	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREVB]);
	glBufferData(GL_ARRAY_BUFFER,model.uvs.size() * sizeof(model.uvs[0]),&model.uvs[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALVB]);
	glBufferData(GL_ARRAY_BUFFER,model.normals.size() * sizeof(model.normals[0]),&model.normals[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vab[INDICESVB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,model.Indices.size() * sizeof(model.Indices[0]),&model.Indices[0],GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

OBJLoader::OBJLoader(void)
{
}


OBJLoader::~OBJLoader(void)
{
}

Model OBJLoader::loadOBJ(std::string path)
{
	printf("Loading OBJ file %s...\n", path.c_str());

	std::vector<Vector3> temp_vertices; 
	std::vector<Vector2> temp_uvs;
	std::vector<Vector3> temp_normals;
	std::vector<GLuint> vertexIndices,uvIndices,normalIndices;


	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Impossible to open the file %s ",path.c_str());
		return Model();
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
				printf("File %s cannot be read",path.c_str());
				return Model();
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
	Model model;
	for(unsigned int i=0;i<temp_vertices.size();i++)
	{
		model.vertices.push_back(temp_vertices[i]);
	}
	for(unsigned int i=0;i<temp_uvs.size();i++)
	{
		model.uvs.push_back(temp_uvs[i]);
	}
	for(unsigned int i=0;i<temp_normals.size();i++)
	{
		model.normals.push_back(temp_normals[i]);
	}
	for(unsigned int i = 0;i<vertexIndices.size();i++)
	{
		model.Indices.push_back(vertexIndices[i] - 1);
	}
	for(unsigned int i = 0;i<uvIndices.size();i++)
	{
		model.Indices.push_back(uvIndices[i] - 1);
	}
	for(unsigned int i = 0;i<normalIndices.size();i++)
	{
		model.Indices.push_back(normalIndices[i] - 1);
	}
	model.index.vertexIndex=vertexIndices.size();
	model.index.uvIndex=uvIndices.size();
	model.index.normalIndex=vertexIndices.size();

	for( unsigned int i=0; i<model.index.vertexIndex; i++ )
	{
		Vector3 vertex = model.vertices[ vertexIndices[i] - 1 ];
		Vector2 uv = temp_uvs[ uvIndices[i] - 1 ];
		Vector3 normal = temp_normals[ normalIndices[i] - 1 ];
		model.Vertices.push_back(Vertex(vertex,uv,normal));
	}
	return model;
}

Model::Model()
{
	
}