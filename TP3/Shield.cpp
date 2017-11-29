#include "Shield.h"
using namespace tp3;

Color tp3::Shield::choixCouleur()
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
Shield::Shield(Vector2f position, Texture& texture)
{
	srand(time(NULL));
	ptsShield = rand() % 3 + 1;
	setPosition(position);
	setTexture(texture);
	setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	setScale(getScale().x * 0.2, getScale().y * 0.2);
	setColor(choixCouleur());
}


Shield::~Shield()
{
}

