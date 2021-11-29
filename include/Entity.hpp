#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Entity {
public:

	Entity(float x, float y, float w, float h);
	~Entity() {
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
//			std::cout << "Error: " << SDL_GetError() << ": " << texture <<std::endl;
		}
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	float getX();
	float getY();
	void setTexture(SDL_Texture *texture) {
		this->texture = texture;
	}
	void setDestRect(SDL_Rect destRect) {
		destinationRect = destRect;
	}
	SDL_Texture* getTexture();
	SDL_Rect getFrame();
	SDL_Rect getDestRect();
private:
	float x, y;
	SDL_Rect frame;
	SDL_Rect destinationRect; //The rectangle's position and size that the sprite is loaded on
	SDL_Texture *texture = nullptr;
};
