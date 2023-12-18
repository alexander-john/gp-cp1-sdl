/*
* This program was written by Alexander John for educational purposes.
* 
*/

#pragma once
#include <SDL.h>

// Game class
class Game {
public:
	// Constructor
	//Game();

	// Initialize game
	bool initialize();

	// Runs game loop until game is over
	void runLoop();

	// Shutdown game
	void shutdown();

private:
	// Helper functions for game loop
	void processInput();
	//void updateGame();
	//void generateOutput();

	// Window by SDL
	SDL_Window* mWindow;

	// Continue to run?
	bool mIsRunning;
};