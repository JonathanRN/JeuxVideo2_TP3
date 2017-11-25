#include "Enemy.h"

using namespace tp3;

Color tp3::Enemy::choixCouleur()
{
	Color couleur;
	srand(time(NULL));
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

Enemy::Enemy(Vector2f position, Texture &texture)
{
	setPosition(position);
	setTexture(texture);
	setColor(choixCouleur());
}


Enemy::~Enemy()
{
}
