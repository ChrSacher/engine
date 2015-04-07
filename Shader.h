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
#include "Math/3DMath.h"
#include "Transform.h"
#include "Camera3d.h"
#include "Material.h"
#include "Objekt.h"
#include "Lighting.h"

const int static MAXPOINTLIGHTS = 4;
const int static MAXSPOTLIGHTS = 4;


class Shader
{
public:
	Shader();
	~Shader(void);

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
	std::map<std::string,GLint> uniforms;
	GLint getUniformLocation(const std::string& uniformName);
	//setters
	
	void setUniform(std::string uniformName, int value);
	void setUniform(std::string uniformName, bool value);
	void setUniform(std::string uniformName, float value);
	void setUniform(std::string uniformName, Vector3 value);
	void setUniform(std::string uniformName, Vector4 value);
	void setUniform(std::string uniformName, Matrix4 value);
	void setUniform(std::string uniformName,BaseLight value);
	//uniforms setters
	void setmodelMatrix(Transform &transform);
	void setviewMatrix(Camera3d &view);
	void setbaseColor(Vector3 Color);
	void setbaseColor(Vector4 Color);
	void setSpecular(Material &material);
	void setCameraPos(Camera3d &view);
	void updateMaterial(Material &material); //kann man auch überladen übersichtshalber mach ich das erst später
	void updateCamera(Camera3d &camera);
	void updateObjekt(Objekt &object);
	void updateDirectionLight(DirectionalLight &light);
	void updateAmbientLight(AmbientLight &ambient);
	void updatePointLight(std::string uniformname ,PointLight &point);
	void updatePointLights(std::vector<PointLight> &point);
	void updateSpotLight(std::string uniformname ,SpotLight &spot);
	void updateSpotLights(std::vector<SpotLight> &spot);
	void updateFog(Fog &fog);
	//

    int _numAttributes;
	std::vector<GLuint> attachedShaders;
    void compileShader(const std::string& filePath, GLuint id);

    GLuint _programID;
	enum
	{
		TRANSFORM_U,
		VIEW_MATRIX,
		NUM_UNIFORMS
	};
};

class BasicShader
{
	BasicShader();
	~BasicShader();
	void addProgram(std::string path,int type);
	void use();
	void unuse();
	GLuint _programID;
	int _numAttributes;
};



#endif
