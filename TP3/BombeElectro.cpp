#include "BombeElectro.h"
using namespace tp3;


BombeElectro::BombeElectro(Vector2f position, Texture& texture) :Bonus(position, texture)
{
	setColor(choixCouleur());
}

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


BombeElectro::~BombeElectro()
{
}
