/*
* This program was written by Alexander John for educational purposes.
* 
*/

#include "Game.h"

int main(int argc, char** argv) {
	// crate game object
	Game game;

	// create success bool
	bool success = game.initialize();

	// if success is true
	if (success) {
		game.runLoop();
	}

	game.shutdown();

	return 0;
}