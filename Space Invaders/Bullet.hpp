#pragma once

#include <VirtualGameConsole/VGCVector.h>

struct Bullet {
	Bullet(VGCVector position, VGCVector direction) :
		position(position), direction(direction) {}

	VGCVector position;
	VGCVector direction;
};
