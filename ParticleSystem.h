#pragma once
#include "Math/Vectors.h"
#include "Math/Matrices.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <vector>
#include "Shader.h"
#include "Camera3d.h"
#include <random>

class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();
	GLuint vao;
	GLuint particles_color_buffer;
	GLuint particles_position_buffer;
	Shader *shader;
	Camera3d *camera;
	int lastParticle;
	void update();
	void draw();
};

class Particle                                                                         
{ 
public: 
	Particle()
	{
		pos = Vector3();
		vel = Vector3();
		color = Vector4();
		lifeTime=size=type=0;
	}
	Particle(Vector3 Pos,Vector3 Vel,Vector4 Color)
	{
		pos = Pos;
		vel = Vel;
		color = Color;
		lifeTime=size=type=0;
	}
	~Particle(){};
   Vector3 pos; 
   Vector3 vel; 
   Vector4 color; 
   float lifeTime; 
   float size; 
   int  type;
   float cameradistance;
   bool operator<(const Particle& that) const
   {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};

