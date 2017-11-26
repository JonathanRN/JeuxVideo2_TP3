#include "Projectile_Enemy.h"
using namespace tp3;


Projectile_Enemy::Projectile_Enemy(Vector2f position, float vitesse, Texture& texture, Color color) : Projectile(position, color, 100)
{
	setTexture(texture);
	this->vitesse = vitesse;
	setScale(getScale().x * 0.1, getScale().y *0.1);
	setOrigin(texture.getSize().x/2, texture.getSize().y / 2);

}
void Projectile_Enemy::anim(int direction)
{

}

void tp3::Projectile_Enemy::initGraphiques()
{
}

Projectile_Enemy::~Projectile_Enemy()
{
}
