#include "Enemy2.h"
using namespace tp3;


Enemy2::Enemy2(Vector2f position, Texture &texture, Color color) :Enemy(position, texture, color)
{
	setScale(getScale().x * 0.8, getScale().y * 0.8);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 4;
	dommageTir = 1;
	vitesse = 4;
	ptsVie = 5;
}


Enemy2::~Enemy2()
{
}

void Enemy2::action(Vaisseau &cible)
{
	float distance0 = sqrt(pow(cibleX - enemyX, 2) + pow(cibleY - enemyY, 2));


}
