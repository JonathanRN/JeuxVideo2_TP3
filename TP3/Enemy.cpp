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

void tp3::Enemy::action(Vaisseau & cible)
{
}

void tp3::Enemy::notifier(Sujet * sujet)
{
	if (typeid(*sujet) == typeid(Bombe))
	{
		Bombe* bombe = dynamic_cast<Bombe*>(sujet);
		if (bombe->getColor() != getColor())
		{
			int distance = sqrt(pow(bombe->getPosition().x - this->getPosition().x, 2) + pow(bombe->getPosition().y - this->getPosition().y, 2));
			ptsVie -= (750 - distance) / 20;
			std::cout << "Ouch esti" << std::endl;
		}
	}
	if (typeid(*sujet) == typeid(BombeElectro))
	{
		canShoot = false;
	}
	
}
