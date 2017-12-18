#include "Bombe.h"
using namespace tp3;


Bombe::Bombe(Vector2f position, Texture& texture) :Bonus(position, texture)
{
	setColor(choixCouleur());
	setScale(getScale().x * 2, getScale().y * 2);
}

/// <summary>
/// Choisis une couleur aléatoirement selon rouge, magenta ou jaune
/// </summary>
/// <returns></returns>
Color tp3::Bombe::choixCouleur()
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
/// Gère l'animation de la bombe
/// </summary>
void tp3::Bombe::anim()
{
	if (animation < ANIMATION_MAXIMALE)
	{
		animation++;

		if (animation % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left += image;
			setTextureRect(rectangleAnimation);
		}
		if (animation == 50)
		{
			animTermine = true;
		}
	}
}

/// <summary>
/// Init graphiques
/// </summary>
void tp3::Bombe::initGraphiques()
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

Bombe::~Bombe()
{
}
