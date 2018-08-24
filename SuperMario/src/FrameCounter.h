#pragma once
#include "header.h"

class CFrameCounter
{
public:
	CFrameCounter();
	void start();
	void stop();
	float getAverageFPS();
	void increaseFrames();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;
	bool mStarted;
	int countedFrames;
	Uint32 getTicks();
};