#include "Background.h"
#include "Core.h"


CBackground::CBackground(void) {
	pos = 2;
	bgTexture = NULL;
}

CBackground::~CBackground(void) {
	if (bgTexture != NULL) {
		SDL_DestroyTexture(bgTexture);
		bgTexture = NULL;
	}
}

void CBackground::loadFile(SDL_Renderer* renderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load("images/backgrounds.png");
	if (loadedSurface == NULL)
	{
		printf("Unable to load background! SDL_image Error: %s\n", IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		bgTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create background texture! SDL Error: %s\n", SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void CBackground::update(Action action) {
	if (action == RIGHT) {
		pos += getTime()->getDeltaTime() * 20;
	}

	if (action == LEFT) {
		pos -= getTime()->getDeltaTime() * 20;
	}

	if (pos > 512 - renderQuad.w) {
		pos = 2;
	}

	if (pos < 2) {
		pos = 512 - renderQuad.w;
	}

	renderQuad.x = pos;
}

void CBackground::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bgTexture, &renderQuad, NULL);
}