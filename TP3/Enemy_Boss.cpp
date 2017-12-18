#include "Enemy_Boss.h"

using namespace tp3;

Enemy_Boss::Enemy_Boss(Vector2f position, Texture &texture, Color color, int num):Enemy(position, texture, color, num)
{
	setScale(getScale().x * 0.8, getScale().y * 0.8);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 2;
	dommageTir = 0;
	vitesse = 1.5f;
	ptsVie = 2;
	directionY = 1;
	direction = -1;
	isReady = false;
	posX = 300;
}


Enemy_Boss::~Enemy_Boss()
{
}

/// <summary>
/// Se fait appeler par le composite
/// </summary>
void tp3::Enemy_Boss::bouger()
{
	float enemyX = getPosition().x;
	float enemyY = getPosition().y;
	float centreX = 1280 / 2;
	float centreY = 720 / 2;

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

	if (!isReady)
	{
		move(-direction*vitesse, 0);
		if (direction == -1 && getPosition().x > posX)
		{
			isReady = true;
		}
		else if (direction == 1 && getPosition().x < LARGEUR - posX)
		{
			isReady = true;
		}
	}

	if (isReady)
	{
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
}

void tp3::Enemy_Boss::arreter()
{
	//vitesse = 0;
}

void tp3::Enemy_Boss::action(Vaisseau & cible)
{
	
}
