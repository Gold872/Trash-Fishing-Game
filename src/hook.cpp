#include "Hook.hpp"

void Hook::setHooked(bool val) {
	hooked = val;
}
bool Hook::isHooked() {
	return hooked;
}
Hook::Hook(int w, int h) : Entity(0, 0, 550, 550) {
	setX(0);
	setY(0);
	this->hook_width = w;
	this->hook_height = h;
	hooked = false;
}
