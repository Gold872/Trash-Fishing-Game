#include "Game.hpp"
#include <SDL2/SDL.h>

Game game(20);

int main(int argc, char **argv) {

	game.initialize();
	game.spawnFish();

	while (game.isRunning()) {
		game.mainLoop();
	}

	return 0;
}
