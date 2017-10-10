#include "Enemy.hpp"

void Enemy::Draw() const {
	VGCDisplay::renderRectangle(
		VGCRectangle(position, size.getX(), size.getY()),
		color, { 0, 0 }, true
	);
}
