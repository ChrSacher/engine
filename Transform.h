#pragma once

#include "Math/Vectors.h" 
#include "Math/Matrices.h"
 
class Transform
{
public:
	Transform(const Vector3 &pos = Vector3() ,const Vector3 &rot = Vector3(),const Vector3 &scale = Vector3(1.0f,1.0f,1.0f));
	~Transform(void);
	Vector3 pos;
	Vector3 rot;
	Vector3 sca;
	Matrix4 modelMatrix;
	inline Vector3& getPos(){return pos;};
	inline Vector3& getRot(){return rot;};
	inline Vector3& getScale(){return sca;};

	void setPos(Vector3& Pos);
	void setRot(Vector3& Rot);
	void setScale(Vector3& Scale);
	bool update;
	Matrix4 getMatrix() {if(update){ calculateMatrix();}return modelMatrix;};

	void calculateMatrix();
};

