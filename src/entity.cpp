#include <Entity.hpp>
#include <iostream>

Entity::Entity(float x, float y, float w, float h) {
	frame.x = x;
	frame.y = y;
	frame.w = w;
	frame.h = h;
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
