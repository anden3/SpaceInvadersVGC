#pragma once

#include <string>
#include <vector>

#include <VirtualGameConsole/VGCDisplay.h>

static const int    ENEMY_COLLISION_DAMAGE		= 10;
static const double ENEMY_EXPLOSION_DURATION	= 1.0;

struct Bullet;

class Enemy {
public:
	Enemy(VGCVector position, VGCVector direction, VGCImage* aliveSprite, VGCImage* deadSprite) :
		position(position), direction(direction), aliveSprite(aliveSprite), deadSprite(deadSprite) {}

	int speed = 3;
	int value = 100;
	int health = 10;

	int bulletSpeed = 10;
	int bulletDamage = 5;

	bool blownUp = false;

	double lastFire = 0.0;

	// When this enemy (if ever) got blown up.
	double blownUpTime = 0.0;

	VGCVector position;
	VGCVector direction;

	void BlowUp(double time);
	void Draw() const;

	virtual int						GetSpeed()		const = 0;
	virtual int						GetValue()		const = 0;
	virtual int						GetHealth()		const = 0;
	virtual std::string				GetSpriteName() const = 0;

	virtual void					SetHealth(int health) = 0;

	virtual std::vector<Bullet>		Fire(double time) = 0;

private:
	VGCImage* deadSprite;
	VGCImage* aliveSprite;

	std::string spriteName;
};

class BasicEnemy : public Enemy {
public:
	// Inherit the constructor.
	using Enemy::Enemy;

	int					GetSpeed()		const { return speed; }
	int					GetValue()		const { return value; }
	int					GetHealth()		const { return health; }
	std::string			GetSpriteName() const { return spriteName; }

	void				SetHealth(int health) { this->health = health; }

	std::vector<Bullet> Fire(double time);

private:
	int speed = 2;

	std::string spriteName = "enemy";
};

class ArcEnemy : public Enemy {
public:
	using Enemy::Enemy;

	int					GetSpeed()		const { return speed; }
	int					GetValue()		const { return value; }
	int					GetHealth()		const { return health; }
	std::string			GetSpriteName() const { return spriteName; }

	void				SetHealth(int health) { this->health = health; }

	std::vector<Bullet> Fire(double time);

private:
	int value = 200;

	std::string spriteName = "arcEnemy";
};

class TankEnemy : public Enemy {
public:
	using Enemy::Enemy;

	int					GetSpeed()		const { return speed; }
	int					GetValue()		const { return value; }
	int					GetHealth()		const { return health; }
	std::string			GetSpriteName() const { return spriteName; }

	void				SetHealth(int health) { this->health = health; }

	std::vector<Bullet> Fire(double time);

private:
	int speed  = 1;
	int value  = 200;
	int health = 30;

	std::string spriteName = "tankEnemy";
};

class QuickEnemy : public Enemy {
public:
	using Enemy::Enemy;

	int					GetSpeed()		const { return speed; }
	int					GetValue()		const { return value; }
	int					GetHealth()		const { return health; }
	std::string			GetSpriteName() const { return spriteName; }

	void				SetHealth(int health) { this->health = health; }

	std::vector<Bullet> Fire(double time);

private:
	int speed = 5;
	int value = 200;

	std::string spriteName = "quickEnemy";
};
