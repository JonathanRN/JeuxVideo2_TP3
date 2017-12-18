#include "BombeElectro.h"
using namespace tp3;


BombeElectro::BombeElectro(Vector2f position, Texture& texture) :Bonus(position, texture)
{
	setColor(choixCouleur());
	rectangleAnimation.left = 0;
	rectangleAnimation.top = 0;
}

/// <summary>
/// Choisis une couleure aléatoirement
/// </summary>
/// <returns></returns>
Color tp3::BombeElectro::choixCouleur()
{
	Color couleur;
	static int choix;
	choix = rand() % 3;

	switch (choix)
	{
	case 0:
		couleur = Color::Red;
		break;
	case 1:
		couleur = Color::Magenta;
		break;
	case 2:
		couleur = Color::Yellow;
		break;
	}
	return couleur;
}

/// <summary>
/// Animation de le bombe électro
/// </summary>
void tp3::BombeElectro::anim()
{

	static int direction = 1;
	if (direction == 1)
	{
			animation++;
			if (animation % RHYTME_ANIM == 0)
			{
				rectangleAnimation.left += image;
				setTextureRect(rectangleAnimation);
			}
			if (rectangleAnimation.left >= 460-image)
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

/// <summary>
/// Init graphiques
/// </summary>
void tp3::BombeElectro::initGraphiques()
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



BombeElectro::~BombeElectro()
{
}
