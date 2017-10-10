#include "Player.hpp"

#include "Game.hpp"

#include <map>

#include <VirtualGameConsole/VGCClock.h>
#include <VirtualGameConsole/VGCDisplay.h>
#include <VirtualGameConsole/VGCKeyboard.h>

static const int BULLET_SPEED = 2;
static const double BULLET_FIRE_RATE = 0.2;

static const std::map<VGCKey, VGCVector> MovementKeys = {
	{ VGCKey::ARROW_LEFT_KEY,	{-1,  0 } },
	{ VGCKey::ARROW_UP_KEY,		{ 0, -1 } },
	{ VGCKey::ARROW_RIGHT_KEY,	{ 1,  0 } },
	{ VGCKey::ARROW_DOWN_KEY,	{ 0,  1 } }
};

static const VGCVector BulletDirections[3] = {
	{-1, -1}, {0, -1}, {1, -1}
};

Player::Player(Game* game, VGCVector size, VGCVector position)
	: game(game), size(size), position(position) {}

void Player::Update() {
	auto bullet = bullets.begin();

	while (bullet != bullets.end()) {
		bullet->position += bullet->direction * BULLET_SPEED;

		if (game->CheckIfBulletHitEnemy(*bullet)) {
			bullet = bullets.erase(bullet);
		}
		else {
			++bullet;
		}
	}

	if (VGCKeyboard::isPressed(VGCKey::SPACE_KEY) && (VGCClock::getTime() - lastFire) >= BULLET_FIRE_RATE) {
		lastFire = VGCClock::getTime();

		// Pew pew pew.
		for (auto const &dir : BulletDirections) {
			bullets.emplace_back(position, dir);
		}
	}

	VGCVector newPos = position;

	for (auto const &key : MovementKeys) {
		if (VGCKeyboard::isPressed(key.first)) {
			newPos += key.second;
		}
	}

	// Boundary collision detection.
	if (newPos.getX() >= 0 && newPos.getX() < (game->windowSize.getX() - size.getX())) {
		position.setX(newPos.getX());
	}

	if (newPos.getY() >= 0 && newPos.getY() < (game->windowSize.getY() - size.getY())) {
		position.setY(newPos.getY());
	}
}
