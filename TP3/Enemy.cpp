#include "Enemy.h"

using namespace tp3;

Enemy::Enemy(Vector2f position, Texture &texture, Color color)
{
	setPosition(position);
	setTexture(texture);
	setColor(color);
}


Enemy::~Enemy()
{
}
