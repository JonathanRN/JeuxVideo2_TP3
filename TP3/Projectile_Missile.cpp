#include "Projectile_Missile.h"
using namespace tp3;


Projectile_Missile::Projectile_Missile(Vector2f position, float vitesse, Texture& texture, float angle) : Projectile(position, Color::White, 100)
{
	this->angle = angle;
	setPosition(position);
	this->vitesse = vitesse;
	setTexture(texture);
	setScale(getScale().x * 0.4, getScale().y *0.4);
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}

/// <summary>
/// Animation du missile
/// </summary>
/// <param name="direction">The direction.</param>
void Projectile_Missile::anim(int direction)
{
	if (actif && animation < ANIMATION_MAXIMALE)
	{
		if (animation == 0)
		{
			setScale(getScale().x *direction, getScale().y);
		}
		animation++;
		if (animation % RHYTME_ANIM == 0)
		{
			if (rectangleAnimation.left < 2300) //pour ne pas faire disparaitre le proj a la fin de lanim
			{
				
				rectangleAnimation.left += image;
				setTextureRect(rectangleAnimation);
			}
		}

	}
}

/// <summary>
/// Init graphiques
/// </summary>
void Projectile_Missile::initGraphiques()
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


Projectile_Missile::~Projectile_Missile()
{
}