#pragma once 

typedef struct WSIZE {
	int width;
	int height;

	WSIZE() {}
	WSIZE(int width, int height) : width(width), height(height){}

}WSIZE;

class Program
{
protected:
	SDL_Renderer* pRenderer = nullptr;
public:
	Program() {}
	virtual ~Program() {}

	virtual void OnEngineInit(SDL_Renderer*& const pEngineRenderer) final;
	//virtual void HandleEvent(SDL_Event& const event) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class Engine
{
private:

	Program* program;

	SDL_Window* window;					// SDL window object
	SDL_Renderer* renderer;				// SDL renderer object

	WSIZE windowSize;					// width and height properties represent pixel size of window
	int createWindowFlagsSDL;			// flags for SDL_CreateWindow method
	int createRendererFlagsSDL;			// flags for SDL_CreateRenderer method

	bool assetsInitializedSDL;			// indicates whether or not instance of Enigne has initialized SDL assests
	bool isRunning;						// indicates whether or not instance of Engine is running

	int counter;
	int interval;

public:

	Engine();
	~Engine();

	void SetProgram(Program*& const pProgram);

	void Init();
	void Init(WSIZE size);

	void HandleEvents();
	void Update();
	void Draw();

	void EngineMainLoop();
};




