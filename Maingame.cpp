
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
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4); //4x multisampling     weiß nicht warum aber das muss vor create window gemacht werden obwohl es anderes vorgeschrieben wir
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Open an SDL window
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    if (_window == nullptr)
	{
        fatalError("SDL Window could not be created!");
    }

    //Set up our OpenGL context
	glContext = SDL_GL_CreateContext(_window);
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
	RenderUtil::initGraphics();
	glClearDepth(1.0f);
    //Set the background color to blue
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	SDL_ShowCursor(SDL_FALSE);
	initShaders();
	createObjects();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(_window);
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
				camera->OnMouse(event.motion.x,event.motion.y);
				SDL_WarpMouseInWindow(_window,SCREEN_WIDTH /2,SCREEN_HEIGHT /2);	
				std::cout << event.motion.x<<event.motion.y<<std::endl;
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
						camera->updatePerspectiveMatrix(70.0f,SCREEN_WIDTH,SCREEN_HEIGHT,0.1f,1000.0f);
						//ui->updateOrtho(SCREEN_WIDTH,SCREEN_HEIGHT);
						glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
					};break;
					case SDL_WINDOWEVENT_MAXIMIZED:
					{
						SDL_MaximizeWindow(_window);
						SDL_GetWindowSize(_window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
						camera->updatePerspectiveMatrix(70.0f,SCREEN_WIDTH,SCREEN_HEIGHT,0.1f,1000.0f);
						//ui->updateOrtho(SCREEN_WIDTH,SCREEN_HEIGHT);
						glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
						SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
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
	if(input.isKeyDown(SDLK_w))
	{
		camera->moveforward();
	}
	if(input.isKeyDown(SDLK_s))
	{
		camera->movebackward();
	}
	if(input.isKeyDown(SDLK_q))
	{
		camera->raise();
	}
	if(input.isKeyDown(SDLK_e))
	{
		camera->sink();
	}
	if(input.isKeyDown(SDLK_a))
	{
		camera->strafeleft();
	}
	if(input.isKeyDown(SDLK_d))
	{
		camera->straferight();
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
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//sky->renderSkybox();
	//normal
	shader->use();
	static int counter;
	counter++;
	shader->updateFog(*fog);
	shader->updateCamera(*camera);
	shader->updateObjekt(*object);
	shader->updateObjekt(*object2);
	shader->updateAmbientLight(*light);;
	shader->updateSpotLight("spotLights[0]",*light3);
	shader->updateDirectionLight(*light2);
	shader->updatePointLight("pointLights[0]",*point);
	shader->unuse();
	ui->draw();
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
	}
	SDL_StopTextInput();	//Text Eingabe anhalten
	close(); //SDL beenden und Resourcen freigeben

	return;
}



void Maingame::close()
{
	SDL_DestroyWindow( _window);
	SDL_GL_DeleteContext(glContext);
	sky->releaseSkybox();
	ui->releaseRenderer();
	delete(camera,light,light2,object,shader,fog,point,sky,ui,object2);
	TextureCache::deleteCache();
	ModelCache::deleteCache();
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

void Maingame::createObjects()
{
	
	camera = new Camera3d(Vector3(0,2,0),70,SCREEN_WIDTH,SCREEN_HEIGHT,0.1f,1000.0f);
	light = new AmbientLight(Vector3(0.2,0.2,0.2));
	light2 = new DirectionalLight(BaseLight(Vector3(1.0f,1.0f,1.0f),0.2f),Vector3(1,15,0));
	object = new Objekt("models/test3.obj",Vector3(0.0f,0.0f,0.0f),Vector3(0.0f,0.0f,0.0f),"",Vector3(0,1,1));
	object2 = new Objekt("models/box.obj",Vector3(0,-2,0),Vector3(0.0f,0.0f,0.0f),"",Vector3(1,1,1));
	object2->transform.setScale(Vector3(1000.0f,0.01,1000));
	point = new PointLight(Vector3(0,1,0),BaseLight(Vector3(1,0,0),0.4),Attenuation(0,0,10),10);
	fog = new Fog(0.05,Vector4(0.5,0.5,0.5,0.5),400,500,0);
	light3 = new SpotLight(PointLight(Vector3(0,10,1),BaseLight(Vector3(1,0,1),1),Attenuation(1,0,0),20),Vector3(1,-1,0),0.2);
	ui = new UIrenderer();
	ui->addButton(Button(Vector2(0,0),Vector2(50,50),Vector4(1,0,0,1),true,""));
	ui->addButton(Button(Vector2(50,50),Vector2(50,50),Vector4(0,0,1,0.1),true,""));
	sky= new Skybox(Vector4(1,1,1,1));
	//sky->loadSkybox("Texture/","posx.png","negx.png","posy.png","negy.png","posz.png","negz.png");
	sky->setCamera(camera);
}

void Maingame::initShaders()
{
	shader = new Shader();
	shader->addVertexShader("Shaders/textureShading.vert");
	shader->addFragmentShader( "Shaders/textureShading.frag");
	shader->addAttribute("position");
	shader->addAttribute("uv");
	shader->addAttribute("normal");	
	shader->linkShaders();
	
}
