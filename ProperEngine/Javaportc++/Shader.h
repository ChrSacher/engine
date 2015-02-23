#pragma once
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <string>
#include "Errors.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include <glm\glm.hpp>
#include "Transform.h"
using namespace glm;
class Shader
{
public:
	Shader(void);
	~Shader(void);
	std::unordered_map<std::string,int> _uniforms;

    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);
    void linkShaders();
	void addVertexShader(std::string path);
	void addGeometryShader(std::string path);
	void addFragmentShader(std::string path);
	void addProgram(std::string path,int type);
	void bind();
		void use();
	void unuse();
	void addUniform(const std::string& uniformname);
    void addAttribute(const std::string& attributeName);
	GLint getUniformLocation(const std::string& uniformName);
	//setters
	void setUniform(std::string uniformName, int value);
	void setUniform(std::string uniformName, float value);
	void setUniform(std::string uniformName, vec3 value);
	void setUniform(std::string uniformName, mat4 value);
	//matrix setters
	void setmodelMatrix(Transform &transform);
private:

    int _numAttributes;

    void compileShader(const std::string& filePath, GLuint id);

    GLuint _programID;
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint uniforms[NUM_UNIFORMS];
};

