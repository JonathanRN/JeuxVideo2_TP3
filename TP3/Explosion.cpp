#include "Explosion.h"
using namespace tp3;


Explosion::Explosion(Vector2f position, Texture& texture)
{
	setPosition(position);
	setTexture(texture);
	setScale(getScale().x * 0.5, getScale().y *0.5);
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}


Explosion::~Explosion()
{
}

/// <summary>
/// Animation de l'explosion
/// </summary>
void tp3::Explosion::anim()
{
	if (animation < ANIMATION_MAXIMALE)
	{
		animation++;

		if (animation % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left += image;
			setTextureRect(rectangleAnimation);
		}
		if (animation == 60)
		{
			animTermine = true;
		}
	}
}

/// <summary>
/// Init graphique
/// </summary>
void tp3::Explosion::initGraphiques()
{
	image = getTexture()->getSize().x / NOMBRES_ANIM;
	int demiTailleX = image / 2;
	int demiTailleY = getTexture()->getSize().y / 2;
	setOrigin(demiTailleX, demiTailleY);

	//Rectangle d'animation
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
	rectangleAnimation.width = image;
	rectangleAnimation.height = getTexture()->getSize().y;

	setTextureRect(rectangleAnimation);
}
