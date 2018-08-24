#include <stdio.h>
#include "game.h"

int main(int argc, char* args[]) {
	bool initialized = initGame();

	if (initialized) {
		gameloop();
	}
	else {
		printf("failed initialization");
	}

	destroyGame();

	return 0;
}