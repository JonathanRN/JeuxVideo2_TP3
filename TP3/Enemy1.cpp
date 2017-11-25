#include "Enemy1.h"
using namespace tp3;


Enemy1::Enemy1(Vector2f position, Texture &texture):Enemy(position, texture)
{
	setScale(getScale().x / 3, getScale().y / 3);
}


Enemy1::~Enemy1()
{
}

void Enemy1::action(Vaisseau& cible)
{
	float cibleX = cible.getPosition().x;
	float cibleY = cible.getPosition().y;
	float enemyX = getPosition().x;
	float enemyY = getPosition().y;
	float distance = sqrt(pow(cibleX - enemyX, 2) + pow(cibleY - enemyY, 2));

	// Gestion de l'angle du zombie
	angle = (atanf((cibleY - enemyY) / (cibleX - enemyX)));

	if (cibleX < enemyX)
	{
		angle = angle + M_PI;
	}

	// Rotation du sprite
	setRotation(angle / M_PI);

	move(VITESSE, 0);
}
