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
		couleur = Color::Yellow;
		break;
	case 2:
		couleur = Color::Green;
		break;
	}
	return couleur;
}

Enemy::Enemy(Vector2f position)
{
	setPosition(position);
	setColor(choixCouleur());
}


Enemy::~Enemy()
{
}
