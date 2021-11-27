#pragma once

#include "Entity.hpp"

class Fish: public Entity {
public:
	Fish();
	~Fish() = default;

	void update();

	void setCaught(bool val) {
		fishCaught = val;
	}
	void setDone(bool val) {
		fishDone = val;
	}
	bool isCaught() {
		return fishCaught;
	}
	bool isDone() {
		return fishDone;
	}

private:
	bool fishCaught;
	bool fishDone; //If it's been caught and taken out of the water
};
