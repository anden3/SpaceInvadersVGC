#pragma once

#include "Bullet.hpp"

#include <string>

#include <VirtualGameConsole/VGCVector.h>

static const int ENEMY_BULLET_DAMAGE = 5;
static const int ENEMY_COLLISION_DAMAGE = 10;

static const double ENEMY_EXPLOSION_DURATION = 1.0;

class Enemy {
public:
	Enemy(VGCVector position, VGCVector direction) :
		position(position), direction(direction)
	{}

	bool blownUp = false;

	// If the last movement by this enemy was downwards.
	bool lastMoveDown = false;

	double lastFire = 0.0;

	// When this enemy (if ever) got blown up.
	double blownUpTime = 0.0;

	int value = 100;

	std::string spriteName = "enemy";

	VGCVector position;
	VGCVector direction;

	void BlowUp(double time) {
		blownUp = true;
		blownUpTime = time;
		spriteName = "explosion";
	}

	Bullet Fire(double time) {
		lastFire = time;
		return Bullet(VGCVector(position), VGCVector(0, 1));
	}
};
