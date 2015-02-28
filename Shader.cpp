#include "Shader.h"


Shader::Shader() : _numAttributes(0)
{
	 _programID = glCreateProgram();
	 if(_programID == 0)
	 {
		 fatalError("failed to create programm");
	 }
}


Shader::~Shader()
{
	glDeleteProgram(_programID);
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



        //We don't need the program anymore.
        glDeleteProgram(_programID);
        //Don't leak shaders either.
        //print the error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link!");
    }
	 uniforms[TRANSFORM_U] = getUniformLocation("modelMatrix");
	 uniforms[VIEW_MATRIX] = getUniformLocation("viewMatrix");
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
    //enable all the attributes we added with addAttribute
    for (int i = 0; i < _numAttributes; i++) 
	{
        glEnableVertexAttribArray(i);
    }
}

//disable the shader
void Shader::unuse() {
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) 
	{
        glDisableVertexAttribArray(i);
    }
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	GLint location =glGetUniformLocation(_programID, uniformName.c_str());
	if(location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " not found");
	}
	return location;
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
	
	void Shader::setUniform(std::string uniformName, Matrix4 value)
	{
		glUniformMatrix4fv(getUniformLocation(uniformName),1,GL_FALSE,&value[0]);
	}

	void Shader::setmodelMatrix(Transform &transform) 
	{
		setUniform("modelMatrix",transform.getMatrix());
	}

	void Shader::setviewMatrix(Camera3d &view)
	{
		setUniform("viewMatrix",view.GetViewProjection());
	};

	void Shader::setbaseColor(Vector3 Color)
	{
		setUniform("baseColor",Color);
	}
	void Shader::setSpecular(Material &material)
	{
		setUniform("specularIntensity",material.getIntensity());
		setUniform("specularPower",material.getPower());
	}
	void Shader::setCameraPos(Camera3d &view)
	{
		setUniform("eyePos",view.getPos());
	}
	void Shader::updateCamera(Camera3d &view)
	{
		setCameraPos(view);
		setviewMatrix(view);
		
	}
	void Shader::updateMaterial(Material &material)
	{
		material.texture.bind();
		setSpecular(material);
		setbaseColor(material.color);
		
	}
	void Shader::updateObjekt(Objekt &object)
	{
		setmodelMatrix(object.transform);
		updateMaterial(object.material);
		object.mesh.draw();
	}

		void Shader::update(Transform &transform,Camera3d &view,Material &material)
	{
		setmodelMatrix(transform);
		setviewMatrix(view);
		setCameraPos(view);
		setSpecular(material);
		setbaseColor(material.color);
		material.texture.bind();
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