#include "Projectile_Beam.h"
using namespace tp3;


Projectile_Beam::Projectile_Beam(Vector2f position, float vitesse, Texture& texture, float angle) : Projectile(position, Color::White, 100)
{
	//setOrigin(0, texture.getSize().y/10);
	setPosition(position);
	setTexture(texture);
	setScale(getScale().x * 10 , getScale().y * 10);
	
	rectangleAnimation.left = 3498;
	rectangleAnimation.top = 0;
}

/// <summary>
/// Animation du laser
/// </summary>
/// <param name="direction">The direction.</param>
void Projectile_Beam::anim(int direction)
{
	    if (animation == 0)
	    {
			setScale(getScale().x * direction, getScale().y);
			setPosition(getPosition().x + 650 * direction, getPosition().y);
		}
		animation++;
		if (animation % RHYTME_ANIM == 0)
		{
			
			rectangleAnimation.left -= image;
			setTextureRect(rectangleAnimation);
		}
		if (rectangleAnimation.left < 0)
		{
			animTermine = true;
		}
}

/// <summary>
/// Init graphiques
/// </summary>
void Projectile_Beam::initGraphiques()
{
	image = getTexture()->getSize().x / NOMBRES_ANIM;
	int demiTailleX = image / 2;
	int demiTailleY = getTexture()->getSize().y / 2;
	setOrigin(demiTailleX, demiTailleY);
	setScale(getScale().x * 0.5, getScale().y * 0.5);
	//Rectangle d'animation
	//rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
	rectangleAnimation.width = image;
	rectangleAnimation.height = getTexture()->getSize().y;

	setTextureRect(rectangleAnimation);
}


Projectile_Beam::~Projectile_Beam()
{
}
