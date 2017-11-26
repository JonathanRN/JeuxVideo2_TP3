#include "Enemy3.h"
using namespace tp3;


Enemy3::Enemy3(Vector2f position, Texture &texture, Color color) :Enemy(position, texture, color)
{
	setScale(getScale().x * -0.5, getScale().y * 0.5);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 5;
	dommageTir = 2;
	vitesse = 2;
	ptsVie = 20;
	direction = 1;
	directionY = 1;
}


Enemy3::~Enemy3()
{
}

void Enemy3::action(Vaisseau &cible)
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

	//Fais bouger les ennemis selon les limites de l'ecran
	if (enemyY - getTexture()->getSize().y / 2 < 0)
	{
		directionY = 1;
	}
	else if (enemyY + getTexture()->getSize().y / 2 > 720)
	{
		directionY = -1;
	}
	move(0, directionY * vitesse);
}
