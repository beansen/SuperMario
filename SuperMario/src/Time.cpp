#include "Time.h"

CTime::CTime(void) {
	frameStartTime = 0;
	frameTime = 0;
}

void CTime::startFrame() {
	frameStartTime = SDL_GetTicks();
}

void CTime::endFrame() {
	frameTime = SDL_GetTicks() - frameStartTime;
}

float CTime::getDeltaTime() {
	return frameTime / 1000.0f;
}