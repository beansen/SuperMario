#pragma once
#include "header.h"
#include "FrameCounter.h"

bool init();
void gameLoop();
void destroy();

CFrameCounter* getFrameCounter();