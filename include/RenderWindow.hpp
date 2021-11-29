#pragma once

#include <Entity.hpp>
#include <SDL2/SDL.h>

class RenderWindow {
public:
	RenderWindow(const char *title, int width, int height);

	SDL_Texture* loadTexture(const char *filePath);
	void clear();
	void fillScreen(int r, int g, int b);
	void render(Entity &entity, int w, int h);
	void display();
	SDL_Renderer* getRenderer() {
		return renderer;
	}
private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
