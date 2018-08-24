#pragma once
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

CFrameCounter* frameCounter = NULL;

bool init() {
	frameCounter = new CFrameCounter();

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
			return false;
		}
	}
	else {
		return false;
	}
	
	return true;
}

void gameLoop() {
	frameCounter->start();

	bool quit = false;

	while (!quit)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Update screen
		SDL_RenderPresent(renderer);

		printf("%d\n", frameCounter->getAverageFPS());
		frameCounter->increaseFrames();
	}
}

void destroy() {

}

CFrameCounter* getFrameCounter() {
	return frameCounter;
}