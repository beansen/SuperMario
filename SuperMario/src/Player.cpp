#include <cmath>
#include "Player.h"
#include "Core.h"

SDL_RendererFlip flip = SDL_FLIP_NONE;
int groundedPos = 0;

CPlayer::CPlayer(void) {
	runningSmall[0] = { 209, 0, 14, 20 };
	runningSmall[1] = { 327, 0, 14, 20 };
	jumpSmall = { 208, 39, 16, 22 };
	playerRect = {0, 540 - 40 - 60, 40, 58};
	horizontalOffset = 0;
	verticalOffset = 0;
	runningState = 0;
	counter = 0;
	state = IDLE;
}

CPlayer::~CPlayer(void) {
	if (playerTexture != NULL) {
		SDL_DestroyTexture(playerTexture);
		playerTexture = NULL;
	}
}

void CPlayer::loadFile(SDL_Renderer* renderer) {
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load("images/mario.png");
	if (loadedSurface == NULL)
	{
		printf("Unable to load background! SDL_image Error: %s\n", IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		playerTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (playerTexture == NULL)
		{
			printf("Unable to create player texture! SDL Error: %s\n", SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void CPlayer::update(Action action) {
	if (action == NONE && isGrounded()) {
		runningState = 0;
		renderRect = &runningSmall[runningState];
	}

	if (action == LEFT) {
		if (horizontalOffset > 0) {
			horizontalOffset -= getTime()->getDeltaTime() * 100;
			playerRect.x = horizontalOffset;
		}
		else {
			horizontalOffset = 0;
		}

		flip = SDL_FLIP_HORIZONTAL;

		if (isGrounded()) {
			state = RUNNING;

			if (counter >= 0.3f) {
				counter = 0;
				runningState++;
				runningState = runningState > 1 ? 0 : 1;
				renderRect = &runningSmall[runningState];
			}
		}
	}

	if (action == RIGHT) {
		if (horizontalOffset < 360 - playerRect.w / 2) {
			horizontalOffset += getTime()->getDeltaTime() * 100;
			playerRect.x = horizontalOffset;
		}
		else {
			horizontalOffset = 360 - playerRect.w / 2;
		}

		flip = SDL_FLIP_NONE;

		if (isGrounded()) {
			state = RUNNING;

			if (counter >= 0.3f) {
				counter = 0;
				runningState++;
				runningState = runningState > 1 ? 0 : 1;
				renderRect = &runningSmall[runningState];
			}
		}
	}

	if (action == JUMP && isGrounded()) {
		state = AIRBORNE;
		groundedPos = playerRect.y;
		verticalOffset = 0;
		renderRect = &jumpSmall;
	}
}

void CPlayer::render(SDL_Renderer* renderer) {
	counter += getTime()->getDeltaTime();

	if (state == AIRBORNE) {
		verticalOffset += getTime()->getDeltaTime() * 5;
		float y = sin(verticalOffset);
		playerRect.y = groundedPos - y * 100;

		if (y <= 0) {
			state = IDLE;
			playerRect.y = groundedPos;
			runningState = 0;
			counter = 0;
			renderRect = &runningSmall[runningState];
		}

	}

	SDL_RenderCopyEx(renderer, playerTexture, renderRect, &playerRect, 0, NULL, flip);
}

bool CPlayer::isGrounded() {
	return state != AIRBORNE;
}

SDL_Rect CPlayer::getPosition() {
	return playerRect;
}