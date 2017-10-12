#pragma once

#include "Enemy.hpp"
#include "Player.hpp"

#include <map>

class Game {
public:
	Game(const int sizeX, const int sizeY);
	~Game();

	bool gameOver = false;

	VGCVector windowSize;

	void RunFrame();
	bool CheckCollision(std::string spriteA, VGCVector posA, std::string spriteB, VGCVector posB);
	bool CheckIfBulletHitEnemy(Bullet bullet);

private:
	int score = 0;

	double lastSpawn = 0.0;

	Player player;
	VGCFont font;

	std::vector<Enemy*> enemies;

	std::vector<Bullet> enemyBullets;
	std::vector<Bullet> playerBullets;

	std::map<std::string, float> enemyTypes;

	std::map<std::string, VGCImage> sprites;
	std::map<std::string, VGCVector> spriteSizes;

	// Black background.
	const VGCColor backgroundColor = VGCColor(255, 0, 0, 0);

	void Draw();
	void UpdateEnemies();
	void SpawnEnemy();
};
