#include "header.h"

enum PlayerState {
	RUNNING,
	IDLE,
	AIRBORNE
};

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void update(Action action);
	void loadFile(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	SDL_Rect getPosition();
	bool isGrounded();

private:
	float counter;
	float horizontalOffset;
	float verticalOffset;
	int runningState;
	SDL_Rect runningSmall[2];
	SDL_Rect jumpSmall;
	SDL_Rect* renderRect;
	SDL_Texture* playerTexture;
	SDL_Rect playerRect;
	PlayerState state;
};