#include "Background.h"
#include "Core.h"
#include "Game.h"

bool canScroll = false;

CBackground::CBackground(void) {
	offset = 2;
	needsSecondCopy = false;
	bgTexture = NULL;

	srcRect[0] = {2, 604, 256, 270};
	srcRect[1] = {258, 604, 256, 270};
	
	dstRect[0] = {0, 0, 720, 540};
	dstRect[1] = {720, 0, 720, 540};

	startPos[0] = 0;
	startPos[1] = 720;
}

CBackground::~CBackground(void) {
	if (bgTexture != NULL) {
		SDL_DestroyTexture(bgTexture);
		bgTexture = NULL;
	}
}

void CBackground::loadFile(SDL_Renderer* renderer) {
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
		if (bgTexture == NULL)
		{
			printf("Unable to create background texture! SDL Error: %s\n", SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void CBackground::update(Action action) {
	if (canScroll) {
		if (action == RIGHT) { 
			offset += getTime()->getDeltaTime() * 100;
			for (int i = 0; i < 2; i++)
			{
				dstRect[i].x = startPos[i] - offset;

				if (dstRect[i].x < -dstRect[i].w) {
					dstRect[i].x = dstRect[i].w;
				}
			}

			if (offset >= 720) {
				startPos[0] = startPos[0] == 0 ? 720 : 0;
				startPos[1] = startPos[1] == 0 ? 720 : 0;
				offset = 0;
			}
		}
	}
}

void CBackground::render(SDL_Renderer* renderer) {
	SDL_Rect playerPos = getPlayer()->getPosition();

	canScroll = playerPos.x >= 360 - playerPos.w / 2;
	
	for (int i = 0; i < 2; i++) {
		SDL_RenderCopy(renderer, bgTexture, &srcRect[i], &dstRect[i]);
	}
}