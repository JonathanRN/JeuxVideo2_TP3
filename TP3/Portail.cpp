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

void tp3::Portail::anim()
{
	if (animation < ANIMATION_MAXIMALE)
	{
		animation++;
		if (animation % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left += image;
			setTextureRect(rectangleAnimation);
		}

	}
}

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
