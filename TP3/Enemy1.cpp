#include "Enemy1.h"
using namespace tp3;


Enemy1::Enemy1(Vector2f position, Texture &texture, Color color, int numFabrique):Enemy(position, texture, color, numFabrique)
{
	setScale(getScale().x * 0.8, getScale().y * 0.8);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 3;
	dommageTir = 0;
	vitesse = 4;
	ptsVie = 3;
	
}


Enemy1::~Enemy1()
{
}

/// <summary>
/// Se fait appeler à chaque update
/// </summary>
/// <param name="cible">The cible.</param>
void Enemy1::action(Vaisseau& cible)
{
	float cibleX = cible.getPosition().x;
	float cibleY = cible.getPosition().y;
	float enemyX = getPosition().x;
	float enemyY = getPosition().y;

	// Gestion de l'angle
	angle = (atanf((cibleY - enemyY) / (cibleX - enemyX)));

	if (cibleX < enemyX)
	{
		angle = angle + M_PI;
	}

	// Rotation du sprite
	setRotation(angle*180 / M_PI);

	setPosition(enemyX + (cos(angle) * vitesse), enemyY + (sin(angle) * vitesse));
}
