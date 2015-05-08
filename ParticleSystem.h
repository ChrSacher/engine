#pragma once
#include "Math/3DMath.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include <vector>
#include "Shader.h"
#include "Camera3d.h"
#include <random>

class Particle                                                                         
{ 
public: 
	Particle()
	{
		pos = Vector3();
		vel = Vector3();
		color = Vector4();
		lifeTime=type=0;
		size = 1;
	}
	Particle(Vector3 Pos,Vector3 Vel,Vector4 Color)
	{
		pos = Pos;
		vel = Vel;
		color = Color;
		size = 1;
		lifeTime=type=0;
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
	void init();
	void update();
	void draw();
	std::vector<Particle> ParticleBuffer;
};



