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
Entity background(0, 0,
		windowRenderer.loadTexture("res/images/background.bmp"));
Entity ocean(0, 0, windowRenderer.loadTexture("res/images/ocean.bmp"));

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
			//Checks if a fish can be hooked
			for (int i = 0; i < fish.size(); i++) {
				if(fish[i].getX() >= hook.getX() - hook.getHookWidth()
						&& fish[i].getX() <= hook.getX() + hook.getHookWidth()
						&& fish[i].getY() >= hook.getY() - hook.getHookHeight()
						&& fish[i].getY() <= hook.getY() + hook.getHookHeight()
						&& !fish[i].isDone() && !hook.isHooked()) {
					fish[i].setCaught(true);
					hook.setHooked(true);
				} else if(hook.isHooked() && fish[i].isCaught() && mouseY < 180) {
					hook.setHooked(false);
					fish[i].setDone(true);
					fish[i].setCaught(false);
				}
			}
			break;
		case SDL_QUIT:
			running = false;
			break;
		}
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
	windowRenderer.fillScreen();
	windowRenderer.render(background, 550, 550);
	windowRenderer.render(ocean, 550, 550);
	SDL_SetRenderDrawColor(windowRenderer.getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawLine(windowRenderer.getRenderer(),
			hook.getX() + hook.getHookWidth() / 2, 0,
			hook.getX() + hook.getHookWidth() / 2, hook.getY());
	for (int i = 0; i < fish.size(); i++) {
		if(!fish[i].isCaught() && !fish[i].isDone()) {
			windowRenderer.render(fish[i], 55, 55);
		} else if(fish[i].isCaught() && !fish[i].isDone()){
			//If the fish is caught then it's attached to the hook
			fish[i].setX(hook.getX());
			fish[i].setY(hook.getY());
			windowRenderer.render(fish[i], 55, 55);
		}
	}
	windowRenderer.render(hook, 55, 55);
	windowRenderer.display();
}

void Game::mainLoop() {
	updateFPS();
	checkInput();
	for (int i = 0; i < fish.size(); i++) {
		fish[i].update();
	}
	draw();
}

void Game::spawnFish() {
	//Generates a random number for the fish position
	srand(time(NULL));
	for (int i = 0; i < fish.size(); i++) {
		int randX = rand() % 1000;
		int randY = rand() % 500 + 180;
		fish[i].setX(randX - 1050);
		fish[i].setY(randY);
	}
}

void Game::initialize() {
	for (int i = 0; i < fishCount; i++) {
		fish.push_back(Fish());
		fish[i].setTexture(windowRenderer.loadTexture("res/images/fish.bmp"));
	}
	hook.setTexture(windowRenderer.loadTexture("res/images/hook.bmp"));
	hook.setY(250);
	background.setTexture(
			windowRenderer.loadTexture("res/images/background.bmp"));
	ocean.setTexture(windowRenderer.loadTexture("res/images/ocean.bmp"));
}
Game::Game(int fishCount) {
	this->fishCount = fishCount;
	running = true;
}
