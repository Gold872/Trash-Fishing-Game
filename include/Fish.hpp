#pragma once

#include "Entity.hpp"

class Fish: public Entity {
public:
	Fish();
	~Fish() = default;

	void update();

	void setCaught(bool val) {
		caught = val;
	}
	void setDone(bool val) {
		done = val;
	}
	bool isCaught() {
		return caught;
	}
	bool isDone() {
		return done;
	}

private:
	bool caught;
	bool done; //If it's been caught and taken out of the water
};
