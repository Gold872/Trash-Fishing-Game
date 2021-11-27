#pragma once

#include "Entity.hpp"

class Trash: public Entity {
public:
	Trash();
	~Trash() = default;

	void update();

	void setCaught(bool val) {
		trashCaught = val;
	}
	void setDone(bool val) {
		trashDone = val;
	}
	bool isCaught() {
		return trashCaught;
	}
	bool isDone() {
		return trashDone;
	}
private:
	bool trashCaught;
	bool trashDone; //If it's caught and taken out of the water
};
