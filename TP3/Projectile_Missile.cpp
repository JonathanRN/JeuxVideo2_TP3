#include "Projectile_Missile.h"
using namespace tp3;


Projectile_Missile::Projectile_Missile(Vector2f position, float vitesse, Texture& texture, float angle) : Projectile(position, Color::Cyan, 100)
{
	this->angle = angle;
	setPosition(position);
	this->vitesse = vitesse;
	setTexture(texture);
	setScale(getScale().x * 0.5, getScale().y *0.5);
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}

void Projectile_Missile::anim(int direction)
{
	if (actif && animation < ANIMATION_MAXIMALE)
	{
		animation++;
		if (animation % RHYTME_ANIM == 0)
		{
			if (rectangleAnimation.top < 350) //pour ne pas faire disparaitre le proj a la fin de lanim
			{
				setScale(0.5 *direction, getScale().y);
				rectangleAnimation.top += image;
				setTextureRect(rectangleAnimation);
			}
		}

	}
}

void Projectile_Missile::initGraphiques()
{
	image = getTexture()->getSize().y / NOMBRES_ANIM;
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


Projectile_Missile::~Projectile_Missile()
{
}