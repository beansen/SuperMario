#include "header.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void update(Action action);
	void loadFile(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	SDL_Rect getPosition();

private:
	float counter;
	float horizontalOffset;
	float verticalOffset;
	int runningState;
	bool grounded;
	SDL_Rect runningSmall[2];
	SDL_Texture* playerTexture;
	SDL_Rect playerRect;
};