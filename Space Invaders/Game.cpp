#include "Game.hpp"

#include <VirtualGameConsole/VGCClock.h>
#include <VirtualGameConsole/VGCRandomizer.h>

#include <sstream>
#include <Windows.h>

#define DBOUT(s)							\
{											\
   std::ostringstream os_;					\
   os_ << s << '\n';\
   OutputDebugString(os_.str().c_str());	\
}

static const int FONT_SIZE = 24;

static const int    ENEMY_SPAWN_RATE = 2;
static const double ENEMY_FIRE_RATE = 0.4;

Game::Game(const int sizeX, const int sizeY) {
	windowSize = VGCVector(sizeX, sizeY);

	font = VGCDisplay::openFont("Times New Roman", FONT_SIZE);

	sprites = {
		{"enemy",		VGCDisplay::openImage("resources/Enemy.png",     1, 1)},
		{"bullet",		VGCDisplay::openImage("resources/Bullet.png",    1, 1)},
		{"player",		VGCDisplay::openImage("resources/Ship.png",      1, 1)},
		{"explosion",	VGCDisplay::openImage("resources/Explosion.png", 1, 1)}
	};

	for (auto const &sprite : sprites) {
		spriteSizes[sprite.first] = VGCVector(
			VGCDisplay::getWidth(sprite.second), VGCDisplay::getHeight(sprite.second)
		);
	}

	// Start player in center of screen.
	player = Player(this, sprites["player"], { sizeX / 2, sizeY / 2 }, { sizeX, sizeY });
}

Game::~Game() {
	for (auto &sprite : sprites) {
		VGCDisplay::closeImage(sprite.second);
	}

	VGCDisplay::closeFont(font);
}

void Game::RunFrame() {
	player.Update();

	UpdateEnemies();
	Draw();
}

void Game::UpdateEnemies() {
	auto enemy = enemies.begin();

	while (enemy != enemies.end()) {
		double currentTime = VGCClock::getTime();

		if (enemy->blownUp) {
			if (currentTime - enemy->blownUpTime >= ENEMY_EXPLOSION_DURATION) {
				enemy = enemies.erase(enemy);
			}
			else {
				++enemy;
			}
			
			continue;
		}

		if ((currentTime - enemy->lastFire) >= ENEMY_FIRE_RATE) {
			enemyBullets.push_back(enemy->Fire(currentTime));
		}

		// Instead of moving diagonally in one step, it moves first one step to the side, and then one step down in order to make it slower.

		VGCVector newPos = enemy->position;

		if (enemy->lastMoveDown) {
			newPos.setX(newPos.getX() + enemy->direction.getX());
		}
		else {
			newPos.setY(newPos.getY() + enemy->direction.getY());
		}

		enemy->lastMoveDown = !enemy->lastMoveDown;

		if (newPos.getX() >= 0 && newPos.getX() < (windowSize.getX() - spriteSizes[enemy->spriteName].getX())) {
			enemy->position.setX(newPos.getX());
		}
		else {
			enemy->direction.setX(enemy->direction.getX() * -1);
			enemy->position.setX(enemy->position.getX() + enemy->direction.getX());
		}

		if (newPos.getY() < windowSize.getY()) {
			enemy->position.setY(newPos.getY());
		}
		else {
			// Delete the enemy if it has gone out of bounds.
			enemy = enemies.erase(enemy);
			continue;
		}

		// Check if enemy has collided with the player.
		if (CheckCollision("player", player.position, "enemy", enemy->position)) {
			enemy->BlowUp(currentTime);
			score += enemy->value;
			player.life -= ENEMY_COLLISION_DAMAGE;
		}

		++enemy;
	}

	auto bullet = enemyBullets.begin();

	while (bullet != enemyBullets.end()) {
		bullet->position += bullet->direction;

		// Removing bullet if it has gone off-screen.
		if (bullet->position.getY() >= windowSize.getY()) {
			bullet = enemyBullets.erase(bullet);
			continue;
		}

		// Check player intersection.
		if (CheckCollision("player", player.position, "bullet", bullet->position)) {
			player.life -= ENEMY_BULLET_DAMAGE;

			bullet = enemyBullets.erase(bullet);
			continue;
		}

		++bullet;
	}

	if (player.life <= 0) {
		gameOver = true;
		return;
	}

	double time = VGCClock::getTime();

	if ((time - lastSpawn) >= ENEMY_SPAWN_RATE) {
		lastSpawn = time;
		SpawnEnemy();
	}
}

void Game::Draw() {
	VGCDisplay::clear(backgroundColor);

	for (auto const &bullet : enemyBullets) {
		VGCDisplay::renderImage(sprites["bullet"], { 0, 0 }, bullet.position, { 0, 0 });
	}

	for (auto const &bullet : player.bullets) {
		VGCDisplay::renderImage(sprites["bullet"], { 0, 0 }, bullet.position, { 0, 0 });
	}

	for (auto const &enemy : enemies) {
		VGCDisplay::renderImage(sprites[enemy.spriteName], { 0, 0 }, enemy.position, { 0, 0 });
	}

	VGCDisplay::renderImage(sprites["player"], { 0, 0 }, player.position, { 0, 0 });
}

void Game::SpawnEnemy() {
	// Make sure that the enemy doesn't spawn clipping the window boundaries.
	int spawnX = VGCRandomizer::getInt(0, windowSize.getX() - spriteSizes["enemy"].getX() - 1);
	int xDirection = VGCRandomizer::getBool(0.5) ? 1 : -1;

	enemies.emplace_back(VGCVector(spawnX, -(spriteSizes["enemy"].getY())), VGCVector(xDirection, 1));
}

bool Game::CheckCollision(std::string spriteA, VGCVector posA, std::string spriteB, VGCVector posB) {
	// Source of algorithm: https://gamedev.stackexchange.com/a/587
	return (std::abs(posA.getX() - posB.getX()) * 2 < (spriteSizes[spriteA].getX() + spriteSizes[spriteB].getX()) &&
		    std::abs(posA.getY() - posB.getY()) * 2 < (spriteSizes[spriteA].getY() + spriteSizes[spriteB].getY()));
}

bool Game::CheckIfBulletHitEnemy(Bullet bullet) {
	auto enemy = enemies.begin();

	while (enemy != enemies.end()) {
		if (enemy->blownUp) {
			++enemy;
			continue;
		}

		if (CheckCollision("bullet", bullet.position, "enemy", enemy->position)) {
			enemy->BlowUp(VGCClock::getTime());
			score += enemy->value;
			return true;
		}

		++enemy;
	}

	return false;
}
