
#include "Maingame.h"

Maingame::Maingame(void)
{
	SCREEN_HEIGHT = 480;
	SCREEN_WIDTH = 640;
	gamestate.playing=true;
	gamestate.paused=false;
	windowed=true;
	maxFPS=60;
	

}


Maingame::~Maingame(void)
{

}

void Maingame::init()
{
	
	//Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Open an SDL window
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    if (_window == nullptr)
	{
        fatalError("SDL Window could not be created!");
    }

    //Set up our OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) 
	{
        fatalError("SDL_GL context could not be created!");
    }

    //Set up glew (optional but recommended)
	glewExperimental = GL_TRUE;
    GLenum error = glewInit();
	
    if (error != GLEW_OK)
	{
        fatalError("Could not initialize glew!");
    }
	std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));
    //Tell SDL that we want a double buffered window so we dont get
    //any flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Set VSYNC
    SDL_GL_SetSwapInterval(1);
	//alpha
	glEnableClientState(GL_VERTEX_ARRAY);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
    //Set the background color to blue
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//SDL_SetRelativeMouseMode(SDL_TRUE);


	//reshape();
	createObjects();
	initShaders();
	fpsLimiter.init(maxFPS);

	return ;
}

void Maingame::handleKeys()
{

	unsigned char key=NULL;
	
	while( SDL_PollEvent( &event ) != 0 ) //Eingaben kontrolieren
	{
		switch(event.type)
		{
			case SDL_QUIT://Fenster wird geschlossen
			{
				gamestate.playing=false;
			};break;
			case SDL_MOUSEMOTION:
			{
				input.setMouseCoords(event.motion.x,event.motion.y);
			};break;
			case SDL_KEYUP:
			{
				input.releaseKey(event.key.keysym.sym);
			}break;
			case SDL_KEYDOWN:
			{
				input.pressKey(event.key.keysym.sym);
			}break;
			case SDL_WINDOWEVENT:
			{
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
					{
						SCREEN_WIDTH = event.window.data1;
						SCREEN_HEIGHT = event.window.data2 ;
						reshape();
					};break;
					case SDL_WINDOWEVENT_MAXIMIZED:
					{
						SCREEN_WIDTH= event.window.data1;
						SCREEN_HEIGHT = event.window.data2;
						SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
						reshape();
						windowed=false;
					};break;
				}
			};break;
			case SDL_MOUSEBUTTONDOWN:
			{
				input.pressKey(event.button.button);
			};break;
			case SDL_MOUSEBUTTONUP:
			{
				input.releaseKey(event.button.button);
			};break;
		}
	}

	if(input.isKeyDown(SDLK_ESCAPE))
	{
		close();
	}
	if(input.isKeyDown(SDLK_ESCAPE))
	{
		close();
	}
	return;
}

void Maingame::update()
{
	input.update();
}

void Maingame::render()
{

	//Color buffer leer machen
	glClearDepth(1000);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	shader->use();
	texture->bind(0);
	static int counter;
	counter++;
	shader->setmodelMatrix(*transform);
	mesh2->draw();
	


	shader->unuse();
	SDL_GL_SwapWindow(_window);
	
}
void Maingame::gameloop()
{
	SDL_StartTextInput(); //text eingabe aktivieren
	while( gamestate.playing )//Solange es nicht beended ist
	{ 
		fpsLimiter.begin();
		handleKeys();
		update();
		
		render();	
		


		fps = fpsLimiter.end();
		static int frameCounter = 0;
		frameCounter++;
        if (frameCounter == 1000) 
		{
            std::cout << fps << std::endl;
            frameCounter = 0;
		}
	}
	SDL_StopTextInput();	//Text Eingabe anhalten
	close(); //SDL beenden und Resourcen freigeben

	return;
}



void Maingame::close()
{
	SDL_DestroyWindow( _window);
	_window = NULL;
	SDL_Quit();
	exit(0);
}

void Maingame::run()
{
	init();
	gameloop();
	close(); //SDL beenden
	return;
}

void Maingame::reshape()
{
	// wenn Fenstergröße verändert wird opengl anpassen
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0f,SCREEN_HEIGHT/SCREEN_HEIGHT,0.1f,1000000.0f);
	glMatrixMode(GL_MODELVIEW);
	//glOrtho(-SCREEN_WIDTH/2, SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, SCREEN_HEIGHT/2, -10000, 10000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Maingame::createObjects()
{
	shader = new Shader();
	mesh2 = new Mesh("models/test.obj");
	mesh = new Mesh("models/test2.obj");
	texture = new Texture("Texture/AngryCloud.png");
	transform = new Transform(vec3(0,0,0),vec3(0,0,0),vec3(0.5f,0.5f,0));
	transform->calculateMatrix();

}

void Maingame::initShaders()
{

	shader->addVertexShader("Shaders/textureShading.vert");
	shader->addFragmentShader( "Shaders/textureShading.frag");
	shader->addAttribute("position");
	shader->addAttribute("uv");
	shader->linkShaders();
}
