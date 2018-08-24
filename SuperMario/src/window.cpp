#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "window.h"

namespace window {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* mainWindow = NULL;
	SDL_Renderer* renderer;
	SDL_Texture* mTexture;

	SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT };
	SDL_Rect clip = { 2, 630, 320, 240 };

	void loadTexture();

	bool init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Create window
			mainWindow = SDL_CreateWindow("Super Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (mainWindow == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					return false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
						return false;
					}

					loadTexture();
				}
			}
		}

		return true;
	}

	void render() {
		renderQuad.x = renderQuad.y = 0;
		renderQuad.w = SCREEN_WIDTH / 2;
		SDL_RenderCopy(renderer, mTexture, &clip, &renderQuad);
		renderQuad.x = SCREEN_WIDTH / 2;
		renderQuad.w = SCREEN_WIDTH;
		SDL_RenderCopy(renderer, mTexture, &clip, &renderQuad);
		SDL_RenderPresent(renderer);
	}

	void destroy() {
		SDL_DestroyTexture(mTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(mainWindow);
		mTexture = NULL;
		renderer = NULL;
		mainWindow = NULL;
		IMG_Quit();
	}

	void loadTexture()
	{
		SDL_Surface* loadedSurface = IMG_Load("images/backgrounds.png");
		if (loadedSurface == NULL)
		{
			printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//Create texture from surface pixels
			mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (mTexture == NULL)
			{
				printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
	}
}