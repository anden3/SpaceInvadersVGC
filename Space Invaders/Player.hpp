#pragma once

#include <vector>

#include "Bullet.hpp"

class Game;
class VGCImage;

class Player {
public:
	Player() {}
	Player(Game* game, VGCVector size, VGCVector position);

	int health = 100;
	VGCVector position;

	std::vector<Bullet> bullets;

	void Update();

private:
	double lastFire = 0.0;

	Game* game;
	VGCVector size;
};
