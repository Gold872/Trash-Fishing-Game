#pragma once

#include "Entity.hpp"

class Hook: public Entity {
public:
	Hook(int w, int h);
	int getHookHeight() {
		return hook_height;
	}
	int getHookWidth() {
		return hook_width;
	}
	void setHooked(bool val);
	bool isHooked();
private:
	bool hooked;
	int hook_width;
	int hook_height;
};
