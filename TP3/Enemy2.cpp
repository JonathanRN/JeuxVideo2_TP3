#include "Enemy2.h"

using namespace tp3;

Enemy2::Enemy2(Vector2f position, Texture &texture, Color color):Enemy(position, texture, color)
{
	setScale(getScale().x * -0.8, getScale().y * 0.8);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 4;
	dommageTir = 1;
	vitesse = 4;
	ptsVie = 5;
	direction = 1;
}


Enemy2::~Enemy2()
{
}

void Enemy2::action(Vaisseau &cible)
{
	float enemyX = getPosition().x;
	float enemyY = getPosition().y;
	float centreX = 1280 / 2;
	float centreY = 720 / 2;
	float distanceAuCentre = centreX - enemyX;

	if (centreX - enemyX > 0 && direction != -1) //Empeche de toujours changer l'orientation
	{
		direction = -1;
		setScale(getScale().x * -1, getScale().y);
	}
	else if (centreX - enemyX < 0 && direction != 1)
	{
		direction = 1;
		setScale(getScale().x * -1, getScale().y);
	}

	/*if (enemyY < 0)
	{
		directionY = 1;
	}
	else if (enemyY > 1280)
	{
		directionY = -1;
	}
	move(0, directionY * vitesse);*/
}
