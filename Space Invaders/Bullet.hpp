#pragma once

#include <VirtualGameConsole/VGCVector.h>

struct Bullet {
	Bullet(VGCVector position, VGCVector direction, int damage, int speed) :
		position(position), direction(direction), damage(damage), speed(speed) {}

	int speed;
	int damage;
	VGCVector position;
	VGCVector direction;
};
