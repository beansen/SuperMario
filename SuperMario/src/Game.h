#include "header.h"
#include <list>
#include "Player.h"
#include "Map.h"

class CGame
{
public:
	CGame();
	~CGame();
	void update(std::list<Action>* actions);
	void init(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);

private:

};

CPlayer* getPlayer();
CMap* getMap();