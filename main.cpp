#include"SDL.h"
#include"engine.h"
#undef main

#include <iostream>



#define MAX_PROGRAMS = 10;



//typedef struct WSIZE {
//	int width;
//	int height;
//}WSIZE;
//
//typedef enum ENGINE_PROGRAM {
//	NO_PROGRAM,
//	TEST_PROGRAM_LINE
//} ENGINE_PROGRAM;

/*class Engine
{
private:
	ENGINE_PROGRAM program;

	SDL_Window* window;					// SDL window object
	SDL_Renderer* renderer;				// SDL renderer object

	WSIZE windowSize;					// width and height properties represent pixel size of window
	int createWindowFlagsSDL;			// flags for SDL_CreateWindow method
	int createRendererFlagsSDL;			// flags for SDL_CreateRenderer method

	bool assetsInitializedSDL;			// indicates whether or not instance of Enigne has initialized SDL assests
	bool isRunning;						// indicates whether or not instance of Engine is running


public:
	unsigned int testCounter;			// temporary int for testing purposes
	unsigned int testLineLength;		// temporary int for testing purposes
	unsigned int testLineStep;			// temporary int for testing purposes


	Engine();
	~Engine();


	void Init();
	void Init(WSIZE size);

	void SetProgram(ENGINE_PROGRAM prg);

	void HandleEvents();
	void Update();
	void Draw();

	void EngineMainLoop();

	void TestProgramLine_SetStep(unsigned int step);
	void TestProgramLine_Update();
	void TestProgramLine_Draw();
};
*/
/*
 *	NAME:
 *
 *	DESC:
 *
 *	ARGS:
*/




/*
 *	NAME: Program::OnEngineInit
 *
 *	DESC:
 *
 *	ARGS: 
 *		pEngineRenderer - 
*/
void Program::OnEngineInit(SDL_Renderer*& const pEngineRenderer )
{
	pRenderer = pEngineRenderer;
}

/*
 *	NAME: Engine::Engine - constructor
 *
 *	DESC: intializes members to a default state
 *
 *	ARGS:
*/
Engine::Engine()
{
	std::cout << "Constructing engine object\n";

	program = nullptr;

	renderer = nullptr;
	window = nullptr;

	createWindowFlagsSDL = 0;
	createRendererFlagsSDL = 0;
	assetsInitializedSDL = false;
	isRunning = false;

	windowSize.width = 640;
	windowSize.height = 480;

}

/*
 *	NAME: Engine::~Engine - destructor
 *
 *	DESC: releases SDL asset memory connected to window and renderer members. resets other members to default state.
 *
 *	ARGS:
*/
Engine::~Engine()
{

	std::cout << "Destroying engine object\n";

	if (!assetsInitializedSDL)
	{
		std::cout << "Subsystem cannot destroy unitialized SDL assets" << std::endl;
	}
	else
	{

		assetsInitializedSDL = false;
		isRunning = false;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		

	}
}

void Engine::SetProgram(Program*& const pProgram)
{
	program = pProgram;
}

/*
 *	NAME: Engine::Init - public method (0 overloads)
 *
 *	DESC: initializes SDL, creates window and renderer assets
 *
 *	ARGS:
*/
void Engine::Init()
{
	int SDLInitAll;
	//int SDLCreateWindow;
	//int SDLCreateRenderer;

	SDLInitAll = SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << "SUBSYSTEM INITIALIZE SDL:  ";
	if (SDLInitAll == 0)
	{
		std::cout << "SUCCEEDED\n";

		//SDL_CreateWindowAndRenderer(windowSize.width, windowSize.height, createWindowFlagsSDL, &window, &renderer);
		window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.width, windowSize.height, createWindowFlagsSDL);
		renderer = SDL_CreateRenderer(window, -1, createRendererFlagsSDL);

		std::cout << "SUBSYSTEM CREATE SDL WINDOW:  ";
		if (window)
		{
			std::cout << "SUCCEEDED\n";
		}
		else
		{
			std::cout << "FAILED\n";
		}

		std::cout << "SUBSYSTEM CREATE SDL RENDERER:  ";
		if (renderer)
		{
			std::cout << "SUCCEEDED\n";
			assetsInitializedSDL = true;

			program->OnEngineInit(renderer);
		}
		else
		{
			std::cout << "FAILED\n";
		}
	}
	else
	{
		std::cout << "FAILED\n";

	}


}


/*
 *	NAME: Engine::Init - public method (1 overloads)
 *
 *	DESC: sets window width and height, calls base Init method which initializes SDL, creates window and renderer assets
 *
 *	ARGS: WSIZE size
*/
void Engine::Init(WSIZE size)
{
	windowSize.width = size.width;
	windowSize.height = size.height;
	Init();

}


/*
 *	NAME: Engine::Handle Events - public method (0 overloads)
 *
 *	DESC: Polls for SDL_Events from the window and executes logic based on event.type
 *
 *	ARGS:
*/
void Engine::HandleEvents()
{

	SDL_Event event;
	SDL_PollEvent(&event);

	// currently just checking for SDL_QUIT event
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}


}

/*
 *	NAME: Engine::Update - public method (0 overloads)
 *
 *	DESC: After SDL events are handled, does any logical work or code updates prior to calling render
 *
 *	ARGS:
*/
void Engine::Update()
{
	// logical code goes here
	program->Update();

}

/*
 *	NAME: Engine::Draw - public method (0 overloads)
 *
 *	DESC: Uses SDL renderer to draw visuals to the window
 *
 *	ARGS:
*/
void Engine::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// ======  other draw code here  =======

	program->Draw();

	// ====================================


	SDL_RenderPresent(renderer);
}

/*
 *	NAME: Engine::MainDrawLoop - public method (0 overloads)
 *
 *	DESC: Starts & controls the main loop that continuously calls Engine::HandleEvents, Engine::Update, and Engine::Render
 *
 *	ARGS:
*/
void Engine::EngineMainLoop()
{

	if (assetsInitializedSDL)
	{
		std::cout << "Instance of Engine starting main loop\n";

		isRunning = true;

		while (isRunning)
		{
			HandleEvents();
			Update();
			Draw();
		}

		std::cout << "Instance of Engine has ended main loop\n";
	}
	else
	{
		std::cout << "ERROR! Cannot start main loop before calling engine Init()\n";
	}

}


class Grid : public Program
{
private:
	int gridSpacing;

public:

	Grid() :gridSpacing(50) {}

	~Grid() {}

	void Update() override final
	{

	}

	void Draw() override final
	{

	}


};


int main()
{

	Engine engine;
	Grid gridProgram;



	engine.Init(WSIZE(750,750));
	engine.EngineMainLoop();




/*
* 
*  Old debug prompts
* 
* 
* 
	char userInput = '\0';


	std::cout << "create new engine object? [y/n]   ";
	std::cin >> userInput;
	if (userInput == 'y')
	{
		engine = new Engine();
		//engine->pJob = pGrid;



		std::cout << "run engine init? [y/n]   ";
		userInput = '\0';
		std::cin >> userInput;

		if (userInput == 'y')
		{
			std::cout << "calling engine object Init() method\n\n";

			engine->Init();


			userInput = '\0';
			std::cout << "run test line program? [y/n]   ";
			std::cin >> userInput;

			if (userInput == 'y')
			{
				unsigned int lineStep = 20;
				
				userInput = '\0';
				std::cout << "use default step of 20? [y/n]   ";
				std::cin >> userInput;
				if (userInput == 'n')
				{
					std::cout << "enter positive integer step: ";
					std::cin >> lineStep;
				}


				std::cout << "setting engine program and line step\n";
				engine->SetProgram(ENGINE_PROGRAM::TEST_PROGRAM_LINE);
				engine->TestProgramLine_SetStep(lineStep);
				
				std::cout << "starting engine main loop\n";
				engine->EngineMainLoop();

			}
			else
			{
				std::cout << "did not call engine EngineMainLoop() method\n";
				std::cout << "goodbye\n";
			}

		}
		else
		{
			std::cout << "did not call engine Init() method\n";
			std::cout << "goodbye\n";
		}

		delete engine;
	}
	else
	{
		std::cout << "did not create engine\n";
		std::cout << "goodbye\n";
	}

*/


	return 0;
}