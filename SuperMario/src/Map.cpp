#include "Core.h"
#include "Game.h"

CMap::CMap(void) {
	offset = 0;
	canScroll = false;
}

CMap::~CMap(void) {
	if (groundTilesTexture != NULL) {
		SDL_DestroyTexture(groundTilesTexture);
		groundTilesTexture = NULL;
	}
}

void CMap::loadFile(SDL_Renderer* renderer) {
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load("images/tiles-ground.png");
	if (loadedSurface == NULL)
	{
		printf("Unable to load background! SDL_image Error: %s\n", IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		groundTilesTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (groundTilesTexture == NULL)
		{
			printf("Unable to create player texture! SDL Error: %s\n", SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void CMap::update(Action action) {
	if (canScroll) {
		if (action == RIGHT) {
			offset += getTime()->getDeltaTime() * 100;
		}
	}
}

void CMap::render(SDL_Renderer* renderer) {
	SDL_Rect playerPos = getPlayer()->getPosition();

	canScroll = playerPos.x >= 360 - playerPos.w / 2;

	renderRect.y = 540 - 72;
	for (int i = 0; i < 20; i++) {
		renderRect.x = i * 36 - offset;
		SDL_RenderCopy(renderer, groundTilesTexture, &topTile, &renderRect);
	}
	renderRect.y = 540 - 36;
	for (int i = 0; i < 20; i++) {
		renderRect.x = i * 36 - offset;
		SDL_RenderCopy(renderer, groundTilesTexture, &middleTile, &renderRect);
	}
}

int CMap::getHeightAtPosition(int x) {
	printf("%f\n", offset);
	if (offset < 380) {
		return 540 - 72;
	} else {
		return 540 + 58;
	}
}