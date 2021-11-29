#include "Game.hpp"
#include "RenderWindow.hpp"
#include "Fish.hpp"
#include "Hook.hpp"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

RenderWindow windowRenderer("Fishing", 550, 550);
Hook hook(50, 50);
Entity ocean(0, 0, 550, 550);
Entity logo(0, 0, 550, 550);

bool Game::isRunning() {
	return running;
}

void Game::checkInput() {
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	hook.setX(mouseX - hook.getHookWidth() / 2);
	hook.setY(mouseY);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (state == MENU) {
				loadGame();
				spawnEntities();
				setState(GAME);
			} else if (state == GAME) {

				//Checks if trash can be hooked
				for (int i = 0; i < trash.size(); i++) {
					if (trash[i].getX() >= hook.getX() - hook.getHookWidth()
							&& trash[i].getX()
									<= hook.getX() + hook.getHookWidth()
							&& trash[i].getY()
									>= hook.getY() - hook.getHookHeight()
							&& trash[i].getY()
									<= hook.getY() + hook.getHookHeight()
							&& !trash[i].isDone() && !hook.isHooked()) {
						trash[i].setCaught(true);
						hook.setHooked(true);
					} else if (hook.isHooked() && trash[i].isCaught()
							&& mouseY < 180) {
						hook.setHooked(false);
						trash[i].setDone(true);
						trash[i].setCaught(false);
						N_TRASH_DONE++;
					}
				}
				//Checks if a fish can be hooked
				for (int i = 0; i < fish.size(); i++) {
					if (fish[i].getX() >= hook.getX() - hook.getHookWidth()
							&& fish[i].getX()
									<= hook.getX() + hook.getHookWidth()
							&& fish[i].getY()
									>= hook.getY() - hook.getHookHeight()
							&& fish[i].getY()
									<= hook.getY() + hook.getHookHeight()
							&& !fish[i].isDone() && !hook.isHooked()) {
						fish[i].setCaught(true);
						hook.setHooked(true);
					} else if (hook.isHooked() && fish[i].isCaught()
							&& mouseY < 180) {
						hook.setHooked(false);
						fish[i].setDone(true);
						fish[i].setCaught(false);
						N_FISH_DONE++;
					}
				}
			}
			break;
		case SDL_QUIT:
			running = false;
			break;
		}
	}
}

void Game::checkCompleted() {
	for (int i = 0; i < trash.size(); i++) {
		if (!trash[i].isDone() && trash[i].getX() > 700) {
			trash[i].setDone(true);
			N_TRASH_DONE++;
		}
	}
	for (int i = 0; i < fish.size(); i++) {
		if (!fish[i].isDone() && fish[i].getX() > 700) {
			fish[i].setDone(true);
			N_FISH_DONE++;
		}
	}
	if (N_FISH_DONE == fish.size() && N_TRASH_DONE == trash.size()) {
		loadMenu();
		setState(MENU);
		restart();
	}
}

void Game::updateFPS() {
	//I think this limits the frame rate but I coped the code from someone else so idk
	lastFrame = SDL_GetTicks();
	if (lastFrame >= lastTime + 1000) {
		lastTime = lastFrame;
		fps = frameCount;
	}
	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < 1000 / 60) {
		SDL_Delay(1000 / 60 - timerFPS);
	}
}

void Game::draw() {
	windowRenderer.clear();
	if (state == MENU) {
		windowRenderer.fillScreen(184, 253, 255);
		windowRenderer.render(logo, 550, 550);
	} else if (state == GAME) {
		windowRenderer.fillScreen(184, 253, 255);
		SDL_SetRenderDrawColor(windowRenderer.getRenderer(), 0, 0, 0, 255);
		SDL_RenderDrawLine(windowRenderer.getRenderer(),
				hook.getX() + hook.getHookWidth() / 2, 0,
				hook.getX() + hook.getHookWidth() / 2, hook.getY());

		for (int i = 0; i < trash.size(); i++) {
			if (!trash[i].isCaught() && !trash[i].isDone()) {
				windowRenderer.render(trash[i], 55, 55);

			} else if (trash[i].isCaught() && !trash[i].isDone()) {
				//If the trash is caught then it's attached to the hook
				trash[i].setX(hook.getX());
				trash[i].setY(hook.getY());
				windowRenderer.render(trash[i], 55, 55);
			}
		}
		for (int i = 0; i < fish.size(); i++) {
			if (!fish[i].isCaught() && !fish[i].isDone()) {
				windowRenderer.render(fish[i], 55, 55);
			} else if (fish[i].isCaught() && !fish[i].isDone()) {
				//If the fish is caught then it's attached to the hook
				fish[i].setX(hook.getX());
				fish[i].setY(hook.getY());
				windowRenderer.render(fish[i], 55, 55);
			}
		}
		windowRenderer.render(hook, 55, 55);
		windowRenderer.render(ocean, 550, 550);
	}

	windowRenderer.display();
}

void Game::mainLoop() {
	if (state == MENU) {
		updateFPS();
		checkInput();
		draw();
	} else if (state == GAME) {
		updateFPS();
		checkInput();
		for (int i = 0; i < fish.size(); i++) {
			fish[i].update();
		}
		for (int i = 0; i < trash.size(); i++) {
			trash[i].update();
		}
		draw();
		checkCompleted();
	}
}

void Game::spawnEntities() {
	//Generates a random number for the fish position
	srand(time(NULL));
	for (int i = 0; i < fish.size(); i++) {
		int randX = rand() % 2000;
		int randY = rand() % 300;
		fish[i].setX(randX - 2050);
		fish[i].setY((randY + 200));
	}
	for (int i = 0; i < trash.size(); i++) {
		int randX = rand() % 2000;
		int randY = rand() % 300;
		trash[i].setX(randX - 2050);
		trash[i].setY((randY + 200));
	}
}

void Game::restart() {
	fish.clear();
	trash.clear();

	N_TRASH_DONE = 0;
	N_FISH_DONE = 0;

	spawnEntities();

}
//Loads the textures needed for the game and destroys the ones for the menu (frees up memory)
void Game::loadGame() {
	SDL_DestroyTexture(logo.getTexture());
	SDL_ShowCursor(false);
	hook.setTexture(windowRenderer.loadTexture("res/images/hook.bmp"));
	ocean.setTexture(windowRenderer.loadTexture("res/images/ocean.bmp"));
	for (int i = 0; i < fishCount; i++) {
		fish.push_back(Fish());
		fish[i].setTexture(windowRenderer.loadTexture("res/images/fish.bmp"));
	}
	for (int i = 0; i < trashCount; i++) {
		trash.push_back(Trash());
		trash[i].setTexture(windowRenderer.loadTexture("res/images/trash.bmp"));
	}
}
//Loads the textures needed for the menu and destroys the ones for the game (frees up memory)
void Game::loadMenu() {
	SDL_DestroyTexture(hook.getTexture());
	SDL_DestroyTexture(ocean.getTexture());
	for(int i = 0; i < fish.size(); i++) {
		SDL_DestroyTexture(fish[i].getTexture());
	}
	for(int i = 0; i < trash.size(); i++) {
		SDL_DestroyTexture(trash[i].getTexture());
	}
	SDL_ShowCursor(true);
	logo.setTexture(windowRenderer.loadTexture("res/images/logo.bmp"));
	std::cout << fish.size() << std::endl;
}

Game::Game(int fishCount, int trashCount) {
	this->fishCount = fishCount;
	this->trashCount = trashCount;
	running = true;
}
