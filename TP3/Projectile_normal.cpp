#include "Projectile_normal.h"
using namespace tp3;


Projectile_normal::Projectile_normal(Vector2f position, float vitesse,Texture& texture): Projectile(position,Color::Blue,100)
{
	setPosition(position);
	this->vitesse = vitesse;
	setTexture(texture);
	setScale(getScale().x * 0.5, getScale().y *0.5);
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}

void Projectile_normal::anim()
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

void Projectile_normal::initGraphiques()
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


Projectile_normal::~Projectile_normal()
{
}
