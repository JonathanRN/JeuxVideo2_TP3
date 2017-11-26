#include "Projectile_Enemy.h"
using namespace tp3;


Projectile_Enemy::Projectile_Enemy(Vector2f position, float vitesse, Texture& texture, Color color) : Projectile(position, color, 100)
{
	setTexture(texture);
	int fistme = 0;
}


Projectile_Enemy::~Projectile_Enemy()
{
}
