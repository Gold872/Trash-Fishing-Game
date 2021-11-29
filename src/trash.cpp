#include "Trash.hpp"

void Trash::update() {
	if(!trashCaught) {
		setX(getX() + 2);
	}
}

Trash::Trash() : Entity(0, 0, 550, 550) {
	setX(0);
	setY(0);
	trashCaught = false;
	trashDone = false;
}
