#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <SDL2/SDL_image.h>

RenderWindow::RenderWindow(const char *title, int width, int height) {
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
		std::cout << "Error initializing window and renderer: "
				<< SDL_GetError();
	}
	SDL_SetWindowTitle(window, title);
}
SDL_Texture* RenderWindow::loadTexture(const char *filePath) {
	SDL_Surface *surface = nullptr;
	SDL_Texture *texture = nullptr;
	surface = SDL_LoadBMP(filePath);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == nullptr) {
		std::cout << "Error loading texture: " << SDL_GetError() << "\n" << std::flush;
	}

	return texture;
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::fillScreen(int r, int g, int b) {
	SDL_Rect tempRect;
	tempRect.x = 0;
	tempRect.y = 0;
	tempRect.w = 550;
	tempRect.h = 550;

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &tempRect);
}

void RenderWindow::render(Entity &entity, int w, int h) {
	SDL_Rect source;
	source.x = entity.getFrame().x;
	source.y = entity.getFrame().y;
	source.w = entity.getFrame().w;
	source.h = entity.getFrame().h;

	SDL_Rect destination;
	destination.x = entity.getX();
	destination.y = entity.getY();
//	destination.w = entity.getFrame().w;
//	destination.h = entity.getFrame().h;
	destination.w = w;
	destination.h = h;

	entity.setDestRect(destination);

	SDL_RenderCopy(renderer, entity.getTexture(), &source, &destination);
}
void RenderWindow::display() {
	SDL_RenderPresent(renderer);
//	SDL_UpdateWindowSurface(window);
}
