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
	float pos;
	SDL_Texture* bgTexture;
	SDL_Rect renderQuad = { 2, 600, 320, 240 };
};