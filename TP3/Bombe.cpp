#include "Bombe.h"
using namespace tp3;


Bombe::Bombe(Vector2f position, Texture& texture) :Bonus(position, texture)
{
	setColor(choixCouleur());
}

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


Bombe::~Bombe()
{
}
