#pragma once

#include "Entity.hpp"
#include "Fish.hpp"
#include "Trash.hpp"
#include <vector>

class Game {
public:
	Game(int fishCount, int trashCount);
	bool isRunning();
	void checkInput();
	void checkCompleted();
	void updateFPS();
	void draw();
	void mainLoop();
	void loadGame();
	void loadMenu();
	void spawnEntities();
	void restart();
	void quit();
	int getFishCount() {
		return fishCount;
	}
	std::vector<Fish> fish;
	std::vector<Trash> trash;

	enum gameState {
		MENU, GAME
	};
	gameState state = MENU;
	void setState(gameState state) {
		this->state = state;
	}
private:
	bool running;
	int fishCount, trashCount;
	int N_FISH_DONE = 0, N_TRASH_DONE = 0;
	int lastFrame, lastTime, frameCount, fps, timerFPS;
};
