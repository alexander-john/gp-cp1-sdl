/*
* This program was written by Alexander John for educational purposes.
* 
*/

#include "Game.h"

// global variables
const int thickness = 15;
const float paddleH = 100.0f;

// class member function definition
Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
{

}

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

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

	return true;
}

// function destroys the SDL_Window and closes SDL
void Game::shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// function keeps running iterations of the game loop until 
// mIsRunning becomes false
void Game::runLoop() {
	while (mIsRunning) {
		processInput();
		updateGame();
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

	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

// function to generate output
void Game::generateOutput() {

	/*
	* In computer graphics, the color buffer is a location in memory
	* containing the color information for the entire screen.
	* The display can use the color buffer for drawing the contents
	* screen. Think of the color buffer as a two dimensional array,
	* where each (x,y) index corresponds to a pixel on the screen.
	* In every frame during the "generate output" phase of the game
	* loop, the game writes graphical output into the color buffer.
	*/

	/*
	* double buffering
	* 
	* Rather than having one color buffer that the game and display must
	* share, you create two seperate color buffers. Then the game and
	* display alternate between the color buffers they use every frame.
	* The idea is that with two seperate buffers, the game can write to one
	* (the back buffer) and, at the same time, the display can read from the
	* other one (the front buffer). After the frame completes, the game and
	* display swap their buffers.
	*/

	// specifying drawing color
	SDL_SetRenderDrawColor(
		mRenderer,
		150,	// R
		50,		// G
		55,		// B
		255		// A
	);

	// clear current buffer with drawing color
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(
		mRenderer,
		50,			// R
		50,			// G
		255,		// B
		255			// A
	);

	// draw top wall
	SDL_Rect wall{
		0,			// top left x
		0,			// top left y
		1024,		// width
		thickness	// height
	};
	// draw rectangle on current buffer
	SDL_RenderFillRect(mRenderer, &wall);

	// draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// swap/ update buffer with rendering performed since
	SDL_RenderPresent(mRenderer);
}

void Game::updateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
}