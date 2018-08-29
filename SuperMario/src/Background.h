#include "header.h"
#include <string>

class CBackground
{
public:
	CBackground();
	~CBackground();
	void update(Action action);
	void loadFile(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);

private:
	float offset;
	bool needsSecondCopy;
	SDL_Texture* bgTexture;
	SDL_Rect srcRect[2];
	SDL_Rect dstRect[2];
	int startPos[2];
};