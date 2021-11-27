#pragma once

#include "Entity.hpp"
#include "Fish.hpp"
#include <vector>

class Game {
public:
	Game(int fishCount);
	bool isRunning();
	void checkInput();
	void updateFPS();
	void draw();
	void mainLoop();
	void initialize();
	void spawnFish();
	void Quit();
	int getFishCount() {
		return fishCount;
	}
	std::vector<Fish> fish;

	enum gameState {
		MENU, GAME
	};
private:
	bool running;
	int fishCount;
	int lastFrame, lastTime, frameCount, fps, timerFPS;
};
