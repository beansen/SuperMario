#pragma once
#include "FrameCounter.h"

CFrameCounter::CFrameCounter(void) {
	mStartTicks = 0;
	mStarted = false;
	countedFrames = 0;
}

void CFrameCounter::start()
{
	//Start the timer
	mStarted = true;
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
}

void CFrameCounter::stop()
{
	//Stop the timer
	mStarted = false;

	//Clear tick variables
	mStartTicks = 0;
}

float CFrameCounter::getAverageFPS() {
	float avgFPS = countedFrames / (getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	return avgFPS;
}

void CFrameCounter::increaseFrames() {
	++countedFrames;
}

Uint32 CFrameCounter::getTicks() {
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//Return the current time minus the start time
		time = SDL_GetTicks() - mStartTicks;
	}

	return time;
}