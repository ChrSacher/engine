#pragma once


#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>
#include "stb_image.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <glm\glm.hpp>
#include "InputManager.h"
#include "timing.h"
#include "Errors.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
struct GameState
{
	bool playing;
	bool paused;
	bool mainmenu;
	bool escapemenu;
	bool drawgrid;
	bool cameramove;

};

class Maingame
{
	public:
		Maingame(void);
		~Maingame(void);

		//bool initGL();//matrizen initialisieren + farbe
		void handleKeys(); //Eingabe 
		void update();//Pro frame update
		void render();//Objekte rendern
		void close(); //Schliessen von SDL + Resourcen
		void run();
		void gameloop();
		void init();
		void reshape();
		void createObjects();
		void initShaders();
		//funktionen


		//verschiede eingabenhandler für übersichtlichkeit
		void resizefull();
		void checkinput();

		//Ende von handler

		//setters

		float fps;
		float _time;
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		bool windowed;
		float maxFPS;

		SDL_Event event;
		SDL_GLContext gContext;//OpenGL context
		SDL_Window* _window;
		GameState gamestate;
		FpsLimiter fpsLimiter;
		InputManager input;
		Shader *shader;
		Mesh *mesh;
		Mesh *mesh2;
		Texture *texture;
		Transform *transform;
};

