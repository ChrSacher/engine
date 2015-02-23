#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
class Transform
{
public:
	Transform(const vec3 &pos = vec3() ,const vec3 &rot = vec3(),const vec3 &scale = vec3(1.0f,1.0f,1.0f));
	~Transform(void);
	vec3 pos;
	vec3 rot;
	vec3 sca;
	mat4 modelMatrix;
	inline vec3& getPos(){return pos;};
	inline vec3& getRot(){return rot;};
	inline vec3& getScale(){return sca;};

	inline void setPos(vec3& Pos){pos = Pos;};
	inline void setRot(vec3& Rot){rot=Rot;};
	inline void setScale(vec3& Scale){sca = Scale;};

	mat4 getMatrix() const {return modelMatrix;};

	void calculateMatrix() ;
};

