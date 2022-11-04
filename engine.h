#pragma once 

typedef struct WSIZE {
	int width;
	int height;
}WSIZE;

typedef enum ENGINE_PROGRAM
{
	NO_PROGRAM,
	TEST_PROGRAM_LINE
} ENGINE_PROGRAM;


class Engine
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
	//Job* pJob;
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

class Program
{
protected:
	SDL_Renderer* pRenderer = nullptr;
public:
	Program() {}
	virtual ~Program() {}

	virtual void OnEngineInit ( SDL_Renderer* ) {}
	virtual void HandleEvent(const SDL_Event* event) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};


class GridProgram : public Program
{
public:

	GridProgram() {}

	void HandleEvent(const SDL_Event* event) final;
	void Update() final;
	void Draw() final;
};