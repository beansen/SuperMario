#include "header.h"

class CMap
{
public:
	CMap();
	~CMap();
	void update(Action action);
	void loadFile(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	int getHeightAtPosition(int x);

private:
	float offset;
	bool canScroll;
	SDL_Texture* groundTilesTexture;
	SDL_Texture* pipesTexture;
	SDL_Rect topTile = {154, 99, 16, 16};
	SDL_Rect middleTile = {154, 116, 16, 16};
	SDL_Rect renderRect = { 0, 540 - 72, 36, 36 };
};