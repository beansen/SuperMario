#include "Game.h"
#include "Core.h"
#include "Background.h"
#include <iostream>

CBackground background;

CGame::CGame(void) {
	
}

void CGame::init(SDL_Renderer* renderer) {
	background.loadFile(renderer);
}

void CGame::update(SDL_Renderer* renderer, std::list<Action>* actions) {
	if (actions->size() > 0) {
		for (std::list<Action>::iterator it = actions->begin(); it != actions->end(); ++it) {
			background.update(*it);
		}
	}

	background.render(renderer);
}