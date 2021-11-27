#include "Fish.hpp"
#include "RenderWindow.hpp"

void Fish::update() {
	if(!fishCaught) {
		setX(getX() + 2);
	}
}

Fish::Fish() : Entity(0, 0, nullptr) {
	setX(0);
	setY(0);
	fishCaught = false;
}
