#include "Enemy2.h"
using namespace tp3;


Enemy2::Enemy2(Vector2f position, Texture &texture, Color color) :Enemy(position, texture, color)
{
<<<<<<< HEAD
<<<<<<< HEAD
	setColor(choixCouleur());
=======
>>>>>>> 784e1cb25bdb16ba1a3c51f492129c5134dd1b94
	setScale(getScale().x * -0.8, getScale().y * 0.8);
=======
	setScale(getScale().x * 0.8, getScale().y * 0.8);
>>>>>>> e745587a866008053729bdd15b461e6a5b6b02dd
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 4;
	dommageTir = 1;
	vitesse = 4;
	ptsVie = 5;
}


Enemy2::~Enemy2()
{
}

void Enemy2::action(Vaisseau &cible)
{
	//float distance0 = sqrt(pow(cibleX - enemyX, 2) + pow(cibleY - enemyY, 2));


}
