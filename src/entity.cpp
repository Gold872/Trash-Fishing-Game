#include <Entity.hpp>
#include <iostream>

Entity::Entity(float x, float y, SDL_Texture *texture) {
	frame.x = 0;
	frame.y = 0;
	frame.w = 550;
	frame.h = 550;
}

float Entity::getX() {
	return x;
}
float Entity::getY() {
	return y;
}
SDL_Texture* Entity::getTexture() {
	return texture;
}
SDL_Rect Entity::getFrame() {
	return frame;
}
SDL_Rect Entity::getDestRect() {
	return destinationRect;
}
