#include "Projectile_Enemy.h"
using namespace tp3;


Projectile_Enemy::Projectile_Enemy(Vector2f position, float vitesse, Texture& texture, Color color) : Projectile(position, color, 100)
{
	setTexture(texture);
	setScale(getScale().x * 0.1, getScale().y *0.1);

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
