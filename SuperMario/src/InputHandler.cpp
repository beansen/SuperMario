#include "InputHandler.h"

std::list<Action>* CInputHandler::getActions() {
	actions.clear();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP]) {
		actions.push_back(UP);
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) { 
		actions.push_back(RIGHT);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		actions.push_back(LEFT);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		actions.push_back(DOWN);
	}
	if (currentKeyStates[SDL_SCANCODE_S]) {
		actions.push_back(JUMP);
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		actions.push_back(FIRE);
	}
	if (actions.size() == 0)
	{
		actions.push_back(NONE);
	}

	return &actions;
}