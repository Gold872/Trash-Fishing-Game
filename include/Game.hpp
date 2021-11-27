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
	void updateFPS();
	void draw();
	void mainLoop();
	void initialize();
	void spawnEntities();
	void Quit();
	int getFishCount() {
		return fishCount;
	}
	std::vector<Fish> fish;
	std::vector<Trash> trash;

	enum gameState {
		MENU, GAME
	};
private:
	bool running;
	int fishCount, trashCount;
	int lastFrame, lastTime, frameCount, fps, timerFPS;
};
