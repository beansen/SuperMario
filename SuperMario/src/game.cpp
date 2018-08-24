#include <SDL.h>
#include "game.h"
#include "window.h"


bool initGame() {
	return window::init();
}

void gameloop() {
	bool quitGame = false;

	while (!quitGame) {
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quitGame = true;
			}
		}

		window::render();
	}

	// handle input
	// Change data (player pos, ai pos)
	// collision
}

void destroyGame() {
	window::destroy();
	SDL_Quit();
}