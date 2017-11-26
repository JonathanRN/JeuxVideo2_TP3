#include "Enemy.h"

using namespace tp3;

void Enemy::initExplosion()
{
	image = getTexture()->getSize().y; // / NOMBRES_ANIM;
	int demiTailleX = getTexture()->getSize().x / 2;
	int demiTailleY = image / 2;
	setOrigin(demiTailleX, demiTailleY);

	//Rectangle d'animation
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
	rectangleAnimation.width = getTexture()->getSize().x;
	rectangleAnimation.height = image;

	setTextureRect(rectangleAnimation);
}

Enemy::Enemy(Vector2f position, Texture &texture, Color color)
{
	setPosition(position);
	setTexture(texture);
	setColor(color);
	initExplosion();
}

Enemy::~Enemy()
{
}

void Enemy::animExplosion()
{
	if (actif && animation < ANIMATION_MAXIMALE)
	{
		animation++;
		if (animation % RHYTME_ANIM == 0)
		{
			rectangleAnimation.top += image;
			setTextureRect(rectangleAnimation);
		}
	}
}
