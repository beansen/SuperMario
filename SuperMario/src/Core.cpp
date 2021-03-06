#pragma once
#include "Core.h"
#include "Game.h"
#include "InputHandler.h"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 540;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

CTime* time = NULL;
CGame* game = NULL;
CInputHandler* inputHandler = NULL;

bool init() {
	time = new CTime();
	game = new CGame();
	inputHandler = new CInputHandler();

	window = SDL_CreateWindow("SDL Super Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window != NULL) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer != NULL)
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return false;
			}
		}
		else
		{
			printf("SDL_CreateRenderer could not initialize! SDL_CreateRenderer Error: %s\n", SDL_GetError());
			return false;
		}
	}
	else {
		printf("SDL_CreateWindow could not initialize! SDL_CreateWindow Error: %s\n", SDL_GetError());
		return false;
	}

	game->init(renderer);
	
	return true;
}

void gameLoop() {
	bool quit = false;

	while (!quit)
	{
		time->startFrame();

		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		std::list<Action>* actions = inputHandler->getActions();
		game->update(actions);
		game->render(renderer);

		//Update screen
		SDL_RenderPresent(renderer);
		time->endFrame();
	}
}

void destroy() {
	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

CTime* getTime() {
	return time;
}