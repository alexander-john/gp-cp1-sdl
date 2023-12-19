/*
* This program was written by Alexander John for educational purposes.
* 
*/

#pragma once
#include <SDL.h>

struct Vector2
{
	float x;
	float y;
};

// Game class
class Game {
public:
	// Constructor
	Game();

	// Initialize game
	bool initialize();

	// Runs game loop until game is over
	void runLoop();

	// Shutdown game
	void shutdown();

private:
	// Helper functions for game loop
	void processInput();
	void updateGame();
	void generateOutput();

	// Window by SDL
	SDL_Window* mWindow;

	// Continue to run?
	bool mIsRunning;

	// renderer
	SDL_Renderer* mRenderer;

	// Number of ticks since start of game
	Uint32 mTicksCount;

	// Direction of paddle
	int mPaddleDir;

	// position of paddle
	Vector2 mPaddlePos;

	// Position of ball
	Vector2 mBallPos;

	// velocity of ball
	Vector2 mBallVel;
};