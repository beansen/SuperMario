#include "Game.h"
#include "Core.h"
#include "Background.h"
#include <iostream>

CBackground background;
CPlayer player;
CMap map;

CGame::CGame(void) {
	
}

void CGame::init(SDL_Renderer* renderer) {
	background.loadFile(renderer);
	player.loadFile(renderer);
	map.loadFile(renderer);
}

void CGame::update(std::list<Action>* actions) {
	for (std::list<Action>::iterator it = actions->begin(); it != actions->end(); ++it) {
		background.update(*it);
		player.update(*it);
		map.update(*it);
	}
}

void CGame::render(SDL_Renderer* renderer) {
	background.render(renderer);
	player.render(renderer);
	map.render(renderer);
}

CPlayer* getPlayer() {
	return &player;
}

CMap* getMap() {
	return &map;
}