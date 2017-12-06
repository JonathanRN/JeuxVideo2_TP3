#include "Projectile_Enemy.h"
using namespace tp3;


Projectile_Enemy::Projectile_Enemy(Vector2f position, float vitesse, Texture& texture, Color color, int direction, float scale) : Projectile(position, color, 100)
{
	setTexture(texture);
	this->vitesse = vitesse;
	setScale(getScale().x * (scale *direction), getScale().y *(scale *direction));
	setOrigin(texture.getSize().x/2, texture.getSize().y / 2);

}
void Projectile_Enemy::anim(int direction)
{
	setScale(getScale().x * direction, getScale().y);
}

void tp3::Projectile_Enemy::initGraphiques()
{
}

Projectile_Enemy::~Projectile_Enemy()
{
}
