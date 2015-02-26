#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <string>
#include "Errors.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Math/Matrices.h" 
#include "Math/Vectors.h"
#include "Transform.h"
#include "Camera3d.h"
#include "Material.h"
 
class Shader
{
public:
	Shader(void);
	~Shader(void);
	Shader(const Shader& other);
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
	void setUniform(std::string uniformName, bool value);
	void setUniform(std::string uniformName, float value);
	void setUniform(std::string uniformName, Vector3 value);
	void setUniform(std::string uniformName, Matrix4 value);
	//uniforms setters
	void setmodelMatrix(Transform &transform);
	void setviewMatrix(Camera3d &view);
	void setbaseColor(Vector3 Color);
	//
	void update(Transform &transform,Camera3d &view,Material &material);

    int _numAttributes;

    void compileShader(const std::string& filePath, GLuint id);

    GLuint _programID;
	enum
	{
		TRANSFORM_U,
		VIEW_MATRIX,
		NUM_UNIFORMS
	};

	GLuint uniforms[NUM_UNIFORMS];
};

static class BasicShader
{
	BasicShader();
	~BasicShader();
	static void addProgram(std::string path,int type);
	static void use();
	static void unuse();
	GLuint _programID;
	 int _numAttributes;
};
#endif
