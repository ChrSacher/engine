#include "Shader.h"

GLuint Shader::currentActiveShader = -1;

Shader::Shader() : _numAttributes(0)
{
	/*create program */
	 _programID = glCreateProgram();
	 if(_programID == 0)
	 {
		 fatalError("failed to create programm");
	 }
	 pipeline = new ShaderObjectPipeLine();
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(_programID);
	delete(pipeline);
	
}
void Shader::addVertexShader(std::string path)
{
	addProgram(path,GL_VERTEX_SHADER);
};

void Shader::addGeometryShader(std::string path)
{
	addProgram(path,GL_GEOMETRY_SHADER);
};

void Shader::addFragmentShader(std::string path)
{
	addProgram(path,GL_FRAGMENT_SHADER);
};

void Shader::addProgram(std::string path,int type)
{
	/* create shader to attach to program*/
	int shader = glCreateShader(type); 
	if (shader == 0) 
	{
        fatalError("shader failed to be created!");
    }
	//Open the file
    std::ifstream shaderFile(path);
	std::cout << "opening shader "  + path << std::endl;
    if (shaderFile.fail()) 
	{
        perror(path.c_str());
        fatalError("Failed to open " + path);
    }

    //File contents stores all the text in the file
    std::string fileContents = "";
    //line is used to grab each line of the file
    std::string line;

    //Get all the lines in the file and add it to the contents
    while (std::getline(shaderFile, line)) 
	{
        fileContents += line + "\n";
    }

    shaderFile.close();

    //get a pointer to our file contents c string;
    const char* contentsPtr = fileContents.c_str();
    //tell opengl that we want to use fileContents as the contents of the shader file
    glShaderSource(shader, 1, &contentsPtr, nullptr);

    //compile the shader
    glCompileShader(shader);

    //check for errors
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        //Provide the infolog in whatever manor you deem best.
        //Exit with failure.
        glDeleteShader(shader); //Don't leak the shader.

        //Print error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader " + path + " failed to compile");
    }
	attachedShaders.push_back(shader);
	glAttachShader(_programID, shader);

	
};




void Shader::linkShaders()
{

    //Link our program
    glLinkProgram(_programID);

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		for(int i = 0;i<attachedShaders.size();i++) glDetachShader(_programID,attachedShaders[i]);
		for(int i = 0;i<attachedShaders.size();i++) glDeleteShader(attachedShaders[i]);
        //We don't need the program anymore.
        glDeleteProgram(_programID);
        //Don't leak shaders either.
        //print the error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link!");
    }	
	for(int i = 0;i<attachedShaders.size();i++) glDetachShader(_programID,attachedShaders[i]);
	for(int i = 0;i<attachedShaders.size();i++) glDeleteShader(attachedShaders[i]);
	
}

//Adds an attribute to our shader. SHould be called between compiling and linking.
void Shader::addAttribute(const std::string& attributeName) 
{
    glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

//enable the shader, and all its attributes
void Shader::bind() 
{
    glUseProgram(_programID);
    //enable all the attributes we added with addAttribute
}

void Shader::use() 
{
    glUseProgram(_programID);
	Shader::currentActiveShader =_programID;
    //enable all the attributes we added with addAttribute
    for (int i = 0; i < _numAttributes; i++) 
	{
        glEnableVertexAttribArray(i);
    }
}


void Shader::unuse() 
{
	//disable the shader
    glUseProgram(0);
	Shader::currentActiveShader = -1;
    for (int i = 0; i < _numAttributes; i++) 
	{
        glDisableVertexAttribArray(i);
    }
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	auto mit = uniforms.find(uniformName);
    
    //check if its not in the map
   if (mit == uniforms.end()) 
   {
		GLint location =glGetUniformLocation(_programID, uniformName.c_str());
		if(location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " not found");
			location = -1;
		}	 
        //Insert it into the map
		uniforms.insert(make_pair(uniformName, location));

        return location; 
    }
   return mit->second;
}

	void Shader::setUniform(std::string uniformName, int value)
	{
		glUniform1i(getUniformLocation(uniformName), value);
	}

	void Shader::setUniform(std::string uniformName, bool value)
	{
		glUniform1i(getUniformLocation(uniformName), value);
	}

	void Shader::setUniform(std::string uniformName, float value)
	{
		glUniform1f(getUniformLocation(uniformName), value);
	}
	
	void Shader::setUniform(std::string uniformName, Vector3 value)
	{
		glUniform3f(getUniformLocation(uniformName), value[0],value[1],value[2]);
	}
	void Shader::setUniform(std::string uniformName, Vector4 value)
	{
		glUniform4f(getUniformLocation(uniformName), value[0],value[1],value[2],value[3]);
	}
	
	void Shader::setUniform(std::string uniformName, Matrix4 value)
	{
		glUniformMatrix4fv(getUniformLocation(uniformName),1,GL_FALSE,&value[0]);
	}

	//standard shader specific settings
	void Shader::setUniform(std::string uniformName,BaseLight value)
	{
		setUniform(uniformName + ".base.intensity",value.getIntensity());
		setUniform(uniformName + ".base.color",value.getColor());
	}

	void Shader::setmodelMatrix(Transform *transform) 
	{
		setUniform("modelMatrix",transform->getMatrix());
		setUniform("MVP[0]",matrices.view * transform->getMatrix());
	}
	void Shader::setmodelMatrices(std::vector<Matrix4*> vectormatrices) 
	{
		std::string string =  "MVP[0]";
		for(int i = 0; i < vectormatrices.size();i++)
		{
			string = "MVP[" + std::to_string(i) + "]";
			setUniform(string,matrices.view * *vectormatrices[i]);
		}
	}
	void Shader::setviewMatrix(Camera3d *view)
	{
		matrices.view = view->GetViewProjection();
	};

	void Shader::setbaseColor(Vector3 Color)
	{
		setUniform("baseColor",Color);
	}
	void Shader::setbaseColor(Vector4 Color)
	{
		setUniform("baseColor",Color);
	}
	void Shader::setSpecular(Material *material)
	{
		setUniform("specularIntensity",material->getIntensity());
		setUniform("specularPower",material->getPower());
	}
	void Shader::setCameraPos(Camera3d *view)
	{
		setUniform("eyePos",view->getPos());
	}
	void Shader::updateCamera(Camera3d *view)
	{
		setCameraPos(view);
		setviewMatrix(view);
		
	}
	void Shader::updateMaterial(Material *material)
	{
		material->texture.bind();
		setUniform("Texture",0);
		setSpecular(material);
		setbaseColor(material->color);
		
	}
	void Shader::updateObject(Object *object)
	{
		setmodelMatrix(object->transform);
		updateMaterial(object->material);
		object->mesh->draw();
	}

	void Shader::updateDirectionLight(DirectionalLight *light)
	{
		setUniform("directionalLight.direction",light->getDirection());
		setUniform("directionalLight.base.color",light->getBaseLight().getColor());
		setUniform("directionalLight.base.intensity",light->getBaseLight().getIntensity());
	}
	void Shader::updateAmbientLight(AmbientLight *ambient)
	{
		setUniform("ambientLight",ambient->ambientLight);
	}

	void Shader::updatePointLight(std::string uniformname ,PointLight *point)
	{
		setUniform(uniformname		   ,point->base);
		setUniform(uniformname + ".pos",point->pos);
		setUniform(uniformname + ".atten.constant",point->attenuation.constant);
		setUniform(uniformname + ".atten.exponent",point->attenuation.exponent);
		setUniform(uniformname + ".atten.linear",point->attenuation.linear);
		setUniform(uniformname + ".range",point->range);


	}
	void Shader::updateFog(Fog *fog)
	{
		setUniform("fog.density",fog->density);
		setUniform("fog.color",fog->color);
		setUniform("fog.start",fog->start);
		setUniform("fog.type",fog->type);
		setUniform("fog.end",fog->end);
	}

	void Shader::updatePointLights(std::vector<PointLight> &point)
	{
		if(point.size() > MAXPOINTLIGHTS)
		{
			fatalError("Too many PointLights passed in\n");
			return;
		}
		for(unsigned int i =0;i<point.size();i++)
		{
			std::string string("pointLights[");
			string.append(std::to_string(i));
			string = string  + "]";
			updatePointLight(string,&point[i]);
		}


	}

	void Shader::updateSpotLight(std::string uniformname ,SpotLight *spot)
	{
		setUniform(uniformname + ".pointLight"	   ,spot->pointLight.base);
		setUniform(uniformname + ".pointLight.pos",spot->pointLight.pos);
		setUniform(uniformname + ".pointLight.atten.constant",spot->pointLight.attenuation.constant);
		setUniform(uniformname + ".pointLight.atten.exponent",spot->pointLight.attenuation.exponent);
		setUniform(uniformname + ".pointLight.atten.linear",spot->pointLight.attenuation.linear);
		setUniform(uniformname + ".pointLight.range",spot->pointLight.range);
		setUniform(uniformname + ".cutoff",spot->cutoff);
		setUniform(uniformname + ".dir",spot->dir);


	}

	void Shader::updateSpotLights(std::vector<SpotLight> &spot)
	{
		if(spot.size() > MAXPOINTLIGHTS)
		{
			fatalError("Too many PointLights passed in\n");
			return;
		}
		for(unsigned int i =0;i<spot.size();i++)
		{
			std::string string("spotLights[");
			string.append(std::to_string(i));
			string = string  + "]";
		}


	}

	void Shader::renderBatch()
	{
		pipeline->renderBatches(this);
	}

	void Shader::addObject(Object* object)
	{
		pipeline->addObject(object);
	}

	void Shader::deleteObject(Object* object)
	{
		pipeline->deleteObject(object);
	}

	void Shader::emptyBatch()
	{
		pipeline->emptyBatch();
	}

	//-------------------------------------------------------------------



	BasicShader::BasicShader()
	{
		_programID = glCreateProgram();
		 if(_programID == 0)
		 {
			 fatalError("failed to create programm");
		 }
		 _numAttributes=0;

	addProgram("BasicShader.vert",GL_VERTEX_SHADER);
	addProgram("BasicShader.frag",GL_FRAGMENT_SHADER);

	  glBindAttribLocation(_programID, _numAttributes++, "positon");
	  glBindAttribLocation(_programID, _numAttributes++, "normal");
	  //Link our program
    glLinkProgram(_programID);

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);



        //We don't need the program anymore.
        glDeleteProgram(_programID);
        //Don't leak shaders either.
        //print the error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link!");
    }
}

	void BasicShader::addProgram(std::string path,int type)
{
	int shader = glCreateShader(type);
	if (shader == 0) 
	{
        fatalError("shader failed to be created!");
    }
	//Open the file
    std::ifstream shaderFile(path);
    if (shaderFile.fail()) 
	{
        perror(path.c_str());
        fatalError("Failed to open " + path);
    }

    //File contents stores all the text in the file
    std::string fileContents = "";
    //line is used to grab each line of the file
    std::string line;

    //Get all the lines in the file and add it to the contents
    while (std::getline(shaderFile, line)) 
	{
        fileContents += line + "\n";
    }

    shaderFile.close();

    //get a pointer to our file contents c string;
    const char* contentsPtr = fileContents.c_str();
    //tell opengl that we want to use fileContents as the contents of the shader file
    glShaderSource(shader, 1, &contentsPtr, nullptr);

    //compile the shader
    glCompileShader(shader);

    //check for errors
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        //Provide the infolog in whatever manor you deem best.
        //Exit with failure.
        glDeleteShader(shader); //Don't leak the shader.

        //Print error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader " + path + " failed to compile");
    }
	 glAttachShader(_programID, shader);

	
};

	void BasicShader::use() 
{
    glUseProgram(_programID);
    //enable all the attributes we added with addAttribute
    for (int i = 0; i < _numAttributes; i++) 
	{
        glEnableVertexAttribArray(i);
    }
}

//disable the shader
void BasicShader::unuse() 
{
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) 
	{
        glDisableVertexAttribArray(i);
    }
}

//-------------------------------------------




 Shader::ObjectInformation::ObjectInformation(Object* newObject, GLuint Offset,GLuint Count)
{
	object = newObject;
	offset = Offset;
	count = Count;
}
 Shader::ObjectInformation::~ObjectInformation()
{

}




 Shader::ObjectBatch::ObjectBatch()
{
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glGenBuffers(NUMBUFFERS,vab);
	lastOffset = 0;
	maxSize = 2000000;
	remainingSize[0] = maxSize;
	remainingSize[1] = maxSize * 2/3; //*2/3 weil es nur vector 2 ist
	remainingSize[2] = maxSize;
		//initiliaze buffer with 2mb
	glBindBuffer(GL_ARRAY_BUFFER,vab[VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER,maxSize,NULL,GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREBUFFER]);
	glBufferData(GL_ARRAY_BUFFER,maxSize * 2 / 3,NULL,GL_DYNAMIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALBUFFER]);
	glBufferData(GL_ARRAY_BUFFER,maxSize,NULL,GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);

	glBindVertexArray(0);

}

 void Shader::ObjectBatch::loadBuffer()
 {
	std::vector<Vector3> positions;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	for(int i = 0;i< objects.size();i++)
	{
		
		
		for(int j = 0;j < objects[i].count;j++)
		{
			positions.push_back(objects[i].object->mesh->model.Vertices[j].getPos());
			uvs.push_back(objects[i].object->mesh->model.Vertices[j].getUV());
			normals.push_back(objects[i].object->mesh->model.Vertices[j].getNormal());
		}

		
		
	}
	glBindBuffer(GL_ARRAY_BUFFER,vab[VERTEXBUFFER]);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Vector3)  * positions.size(),&positions[0]); //load stuff into buffer


	glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREBUFFER]);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Vector2)  * uvs.size(),&uvs[0]);

	glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALBUFFER]);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Vector3)  * normals.size(),&normals[0]);

 }

 void Shader::ObjectBatch::loadBufferLast()
 {

		std::vector<Vector3> positions;
		std::vector<Vector2> uvs;
		std::vector<Vector3> normals;
		int i = objects.size() - 1 ;
		positions.reserve(objects[i].count);
		uvs.reserve(objects[i].count);
		normals.reserve(objects[i].count);
		for(int j = 0;j < objects[i].count;j++)
		{
			positions.push_back(objects[i].object->mesh->model.Vertices[j].getPos());
			uvs.push_back(objects[i].object->mesh->model.Vertices[j].getUV());
			normals.push_back(objects[i].object->mesh->model.Vertices[j].getNormal());
		}
		glBindBuffer(GL_ARRAY_BUFFER,vab[VERTEXBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,lastOffset * sizeof(Vector3),sizeof(Vector3)  * objects[i].count,&positions[0]);

	
		glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,lastOffset * sizeof(Vector2),sizeof(Vector2)  * objects[i].count,&uvs[0]);

		glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,lastOffset * sizeof(Vector3),sizeof(Vector3)  * objects[i].count,&normals[0]);

 }

 void Shader::ObjectBatch::loadBufferIndexToLast(GLuint index)
 {
	 for(int i = index;i< objects.size();i++)
	{
		std::vector<Vector3> positions;
		std::vector<Vector2> uvs;
		std::vector<Vector3> normals;
		positions.reserve(objects[i].count);
		uvs.reserve(objects[i].count);
		normals.reserve(objects[i].count);
		for(int j = 0;j < objects[i].count;j++)
		{
			positions.push_back(objects[i].object->mesh->model.Vertices[j].getPos());
			uvs.push_back(objects[i].object->mesh->model.Vertices[j].getUV());
			normals.push_back(objects[i].object->mesh->model.Vertices[j].getNormal());
		}

		glBindBuffer(GL_ARRAY_BUFFER,vab[VERTEXBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,objects[i].offset * sizeof(Vector3),sizeof(Vector3)  * objects[i].count,&positions[0]);

	
		glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,objects[i].offset * sizeof(Vector2),sizeof(Vector2)  * objects[i].count,&uvs[0]);

		glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,objects[i].offset * sizeof(Vector3),sizeof(Vector3)  * objects[i].count,&normals[0]);
		
	}

	glBindVertexArray(0);
 }

 void Shader::ObjectBatch::loadBufferIndex(GLuint index)
 {
		std::vector<Vector3> positions;
		std::vector<Vector2> uvs;
		std::vector<Vector3> normals;
		positions.reserve(objects[index].count);
		uvs.reserve(objects[index].count);
		normals.reserve(objects[index].count);
		for(int j = 0;j < objects[index].count;j++)
		{
			positions.push_back(objects[index].object->mesh->model.Vertices[j].getPos());
			uvs.push_back(objects[index].object->mesh->model.Vertices[j].getUV());
			normals.push_back(objects[index].object->mesh->model.Vertices[j].getNormal());
		}

		glBindBuffer(GL_ARRAY_BUFFER,vab[VERTEXBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,objects[index].offset * sizeof(Vector3),sizeof(Vector3)  * objects[index].count,&positions[0]);

	
		glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,objects[index].offset * sizeof(Vector2),sizeof(Vector2)  * objects[index].count,&uvs[0]);

		glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALBUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER,objects[index].offset * sizeof(Vector3),sizeof(Vector3)  * objects[index].count,&normals[0]);
 }

 Shader::ObjectBatch::~ObjectBatch()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(NUMBUFFERS,vab);
}

 Shader::ShaderObjectPipeLine::ShaderObjectPipeLine()
{
	batches.push_back(new ObjectBatch());
}
 Shader::ShaderObjectPipeLine::~ShaderObjectPipeLine()
{
	for(int i = 0; i < batches.size();i++)
	{
		delete(batches[i]);
	}
}

void  Shader::ShaderObjectPipeLine::addObject(Object* newObject)
{
	for(int i = 0; i < batches.size();i++)
	{
		for(int j = 0;j < batches[i]->objects.size();j++)
		{
			if(batches[i]->objects[j].object->ID == newObject->ID)
			{
				printf("object is allready in Batch");
				return;
			}
		}
		if(batches[i]->checkSize(newObject))
		{
			batches[i]->addObject(newObject);
			return;
		}
	}
	batches.push_back(new ObjectBatch());
	batches[batches.size() - 1]->addObject(newObject);
}
void  Shader::ShaderObjectPipeLine::deleteObject(Object* removeObject)
{
	for(int i = 0;i < batches.size();i++)
	{
		for(int j = 0;j < batches[i]->objects.size();j++)
		{
				
			if(batches[i]->objects[j].object->ID == removeObject->ID)
			{
				batches[i]->deleteObject(j);
				j--;
				return;
			}
		}
	}
	
}

void Shader::ObjectBatch::deleteObject(GLuint index)
{
	if(!(index == objects.size() -1) )
	{
		for(int i = index; i < objects.size() - 1;i++)
		{
			objects[i + 1].offset = objects[i].offset;
		}
	}
	remainingSize[0] += objects[index].count * sizeof(Vector3 );
	remainingSize[1] += objects[index].count * sizeof(Vector2 );
	remainingSize[2] += objects[index].count * sizeof(Vector3 );
	objects.erase(objects.begin() + index);
	
	loadBufferIndexToLast(index);
	
}

void  Shader::ShaderObjectPipeLine::updateObject(Object* updateObject)
{
		deleteObject(updateObject);
		addObject(updateObject);
}



bool  Shader::ObjectBatch::checkSize(Object* newObject)
{
	GLuint positionsSize,normalSize,textureSize = 0;
			positionsSize = newObject->mesh->model.Vertices.size() * sizeof(Vector3);
			textureSize = newObject->mesh->model.Vertices.size() * sizeof(Vector2);
			normalSize = newObject->mesh->model.Vertices.size() * sizeof(Vector3);
	if(positionsSize <= remainingSize[0] && textureSize <= remainingSize[1] && normalSize <= remainingSize[2])
	{
		return true;
	}
	else return false;
}

void  Shader::ObjectBatch::addObject(Object* newObject)
{
	objects.push_back(ObjectInformation(newObject,lastOffset,newObject->mesh->model.Vertices.size()));
	remainingSize[0] -= newObject->mesh->model.Vertices.size() * sizeof(newObject->mesh->model.Vertices[0].getPos());
	remainingSize[1] -= newObject->mesh->model.Vertices.size() * sizeof(newObject->mesh->model.Vertices[0].getUV());
	remainingSize[2] -= newObject->mesh->model.Vertices.size() * sizeof(newObject->mesh->model.Vertices[0].getNormal());
	lastOffset += newObject->mesh->model.Vertices.size();
	loadBufferLast();
}

void  Shader::ShaderObjectPipeLine::renderBatches(Shader* shader)
{
	for(int i = 0; i < batches.size(); i++)
	{
		batches[i]->render(shader);
	}
}

void  Shader::ObjectBatch::render(Shader *shader)
{
	glBindVertexArray(vao);
	for(int i = 0;i < objects.size();i++)
	{
			shader->setmodelMatrix(objects[i].object->transform);
			shader->updateMaterial(objects[i].object->material);
			glDrawArrays(GL_TRIANGLES,objects[i].offset,objects[i].count);
	}
	glBindVertexArray(0);
}

void Shader::ShaderObjectPipeLine::emptyBatch()
{
	for(int i = 0;i < batches.size();i ++)
	{
		batches[i]->objects.clear();
		batches[i]->emptyBuffer();
	}
}

 void Shader::ObjectBatch::emptyBuffer()
 {

		glBindBuffer(GL_ARRAY_BUFFER,vab[VERTEXBUFFER]);
		glBufferData(GL_ARRAY_BUFFER,maxSize,NULL,GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER,vab[TEXTUREBUFFER]);
		glBufferData(GL_ARRAY_BUFFER,maxSize,NULL,GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER,vab[NORMALBUFFER]);
		glBufferData(GL_ARRAY_BUFFER,maxSize,NULL,GL_DYNAMIC_DRAW);
		lastOffset = 0;
		remainingSize[0] = maxSize;
		remainingSize[1] = maxSize;
		remainingSize[2] = maxSize;
 }
