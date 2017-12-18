#include "Portail.h"
using namespace tp3;


Portail::Portail(Vector2f position, Texture& texture)
{
	setPosition(position);
	setTexture(texture);
	setScale(getScale().x * 0.5, getScale().y *0.5);
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}


Portail::~Portail()
{
}

/// <summary>
/// Animation des portails
/// </summary>
void tp3::Portail::anim()
{
	static int direction = 1;
	if (direction == 1)
	{
		if (animation < ANIMATION_MAXIMALE)
		{
			animation++;
			if (animation % RHYTME_ANIM == 0)
			{
				rectangleAnimation.left += image;
				setTextureRect(rectangleAnimation);
			}
			if (rectangleAnimation.left >= 1920-image)
			{
				direction = -1;
				isReady = true;
			}
			else
			{
				isReady = false;
			}
		}
	}
	else
	{
		if (animation < ANIMATION_MAXIMALE)
		{
			animation--;
			if (animation % RHYTME_ANIM == 0)
			{
				rectangleAnimation.left -= image;
				setTextureRect(rectangleAnimation);
			}
			if (rectangleAnimation.left <= 0)
			{
				animTermine = true;
				std::cout << "true" << std::endl;
				direction = 1;
			}
		}
	}
}

/// <summary>
/// Init graphiques
/// </summary>
void tp3::Portail::initGraphiques()
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
