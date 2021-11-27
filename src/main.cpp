#include "Game.hpp"
#include <SDL2/SDL.h>

Game game(20, 40);

int main(int argc, char **argv) {

	game.initialize();
	game.spawnEntities();

	while (game.isRunning()) {
		game.mainLoop();
	}

	return 0;
}
