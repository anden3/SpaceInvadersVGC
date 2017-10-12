#include "Enemy.hpp"

#include "Bullet.hpp"

void Enemy::BlowUp(double time) {
	blownUp = true;
	blownUpTime = time;
	spriteName = "explosion";
}

void Enemy::Draw() const {
	if (blownUp) {
		VGCDisplay::renderImage(*deadSprite, { 0, 0 }, position, { 0, 0 });
	}
	else {
		VGCDisplay::renderImage(*aliveSprite, { 0, 0 }, position, { 0, 0 });
	}
}

std::vector<Bullet> BasicEnemy::Fire(double time) {
	lastFire = time;
	return{ Bullet(VGCVector(position), VGCVector(0, 1), bulletDamage, bulletSpeed) };
}

std::vector<Bullet>ArcEnemy::Fire(double time) {
	lastFire = time;

	static const VGCVector BulletDirections[3] = {
		{ -1, 1 },{ 0, 1 },{ 1, 1 }
	};

	std::vector<Bullet> bullets;

	for (auto const &dir : BulletDirections) {
		bullets.emplace_back(position, dir, bulletDamage, bulletSpeed);
	}

	return bullets;
}

std::vector<Bullet> TankEnemy::Fire(double time) {
	lastFire = time;
	return{ Bullet(VGCVector(position), VGCVector(0, 1), bulletDamage, bulletSpeed) };
}

std::vector<Bullet> QuickEnemy::Fire(double time) {
	lastFire = time;
	return{ Bullet(VGCVector(position), VGCVector(0, 1), bulletDamage, bulletSpeed) };
}
