/*
* This program was written by Alexander John for educational purposes.
* 
*/

#include "Game.h"

// class member function definition

// if initialization and window creation succeeds function returns true
bool Game::initialize() {
	// initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	// is the intialize successful? 
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// create window
	mWindow = SDL_CreateWindow(
		"Game Programming",	// window title
		100,				// top left x-coordinate of window
		100,				// top left y-coordinate of window
		1024,				// width of window
		768,				// height of window
		0					// flag (0 for no flag)
	);

	// is the window creation successful?
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// create renderer
	mRenderer = SDL_CreateRenderer(
		mWindow,	// window to create renderer for
		-1,			// usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

	);

	return true;
}

// function destroys the SDL_Window and closes SDL
void Game::shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	SDL_DestroyRenderer(mRenderer);
}

// function keeps running iterations of the game loop until 
// mIsRunning becomes false
void Game::runLoop() {
	while (mIsRunning) {
		processInput();
		//updateGame();
		generateOutput();
	}
}

// function to process inputs
void Game::processInput() {
	SDL_Event event;

	// while there are still events in the queue
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// handle different event types
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// if escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

// function to generate output
void Game::generateOutput() {
	// back buffer specifying color
	SDL_SetRenderDrawColor(
		mRenderer,
		150,	// R
		50,		// G
		55,		// B
		255		// A
	);

	// clear back buffer
	SDL_RenderClear(mRenderer);

	// swap the front and back buffers
	SDL_RenderPresent(mRenderer);
}