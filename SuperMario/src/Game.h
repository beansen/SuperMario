#include "header.h"
#include <list>

class CGame
{
public:
	CGame();
	~CGame();
	void update(SDL_Renderer* renderer, std::list<Action>* actions);
	void init(SDL_Renderer* renderer);

private:

};