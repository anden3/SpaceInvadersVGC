#pragma once

#include <VirtualGameConsole/VGCVector.h>

struct Bullet {
	Bullet(VGCVector position, VGCVector direction, int damage) :
		position(position), direction(direction), damage(damage) {}

	int damage;
	VGCVector position;
	VGCVector direction;
};
