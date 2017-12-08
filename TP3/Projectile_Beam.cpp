#include "Projectile_Beam.h"
using namespace tp3;


Projectile_Beam::Projectile_Beam(Vector2f position, float vitesse, Texture& texture, float angle) : Projectile(position, Color::Cyan, 100)
{
	setPosition(position);
	setTexture(texture);
	//setScale(getScale().x * 0.5, getScale().y *0.5);
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}

void Projectile_Beam::anim(int direction)
{
	if (direction == 1)
	{
		animation++;
		if (animation % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left += image;
			setTextureRect(rectangleAnimation);
		}
		if (rectangleAnimation.left >= 460 - image)
		{
			direction = -1;
		}
	}
	else
	{
		animation--;
		if (animation % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left -= image;
			setTextureRect(rectangleAnimation);
		}
		if (rectangleAnimation.left <= 0)
		{
			direction = 1;
		}
	}
}

void Projectile_Beam::initGraphiques()
{
	image = getTexture()->getSize().x / NOMBRES_ANIM;
	int demiTailleX = image / 2;
	int demiTailleY = getTexture()->getSize().y / 2;
	setOrigin(demiTailleX, demiTailleY);
	setScale(getScale().x * 0.5, getScale().y * 0.5);
	//Rectangle d'animation
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
	rectangleAnimation.width = image;
	rectangleAnimation.height = getTexture()->getSize().y;

	setTextureRect(rectangleAnimation);
}


Projectile_Beam::~Projectile_Beam()
{
}
