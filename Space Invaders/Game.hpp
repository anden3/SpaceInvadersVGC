#pragma once

#include "Enemy.hpp"
#include "Player.hpp"

#include <map>

#include <VirtualGameConsole/VGCDisplay.h>

class Game {
public:
	Game(const int sizeX, const int sizeY);
	~Game();

	void RunFrame();
	bool CheckCollision(std::string spriteA, VGCVector posA, std::string spriteB, VGCVector posB);
	bool CheckIfBulletHitEnemy(Bullet bullet);

private:
	bool gameOver = false;

	int score = 0;

	double lastSpawn = 0.0;

	Player player;
	std::vector<Enemy> enemies;

	std::vector<Bullet> enemyBullets;
	std::vector<Bullet> playerBullets;

	VGCFont font;

	std::map<std::string, VGCImage> sprites;
	std::map<std::string, VGCVector> spriteSizes;

	VGCVector windowSize;

	// Black background.
	const VGCColor backgroundColor = VGCColor(255, 0, 0, 0);

	void Draw();
	void UpdateEnemies();
	void SpawnEnemy();
};
