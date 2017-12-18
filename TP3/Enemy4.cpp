#include "Enemy4.h"

using namespace tp3;

Enemy4::Enemy4(Vector2f position, Texture &texture, Color color, int num) :Enemy(position, texture, color, num)
{
	setScale(getScale().x * -0.15, getScale().y * 0.15);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 4;
	dommageTir = 1;
	vitesse = 4;
	ptsVie = 10;
	direction = -1;
	isReady = false;
	posX = 100;
	grosseur = 1.5f;
}


Enemy4::~Enemy4()
{
}

/// <summary>
/// Se fait appeler à chaque update
/// </summary>
/// <param name="cible">The cible.</param>
void Enemy4::action(Vaisseau &cible)
{
	Vector2f enemyPos = getPosition();

	if (!isReady)
	{
		move(direction*vitesse, 0);
		if (direction == 1 && getPosition().x > posX)
		{
			isReady = true;
		}
		else if (direction == -1 && getPosition().x < LARGEUR - posX)
		{
			isReady = true;
		}
		choixCible(hautGauche, enemyPos);

	}
	else
	{	
		if (enemyPos.x <= hautGauche.x && enemyPos.y <= hautGauche.y && target == hautGauche)
		{
			choixCible(basGauche, enemyPos);
			target = basGauche;
		}
		if (enemyPos.x >= basGauche.x && enemyPos.y >= basGauche.y && target == basGauche)
		{
			choixCible(hautDroite, enemyPos);
			target = hautDroite;
		}
		if (enemyPos.x >= hautDroite.x && enemyPos.y <= hautDroite.y && target == hautDroite)
		{
			choixCible(basDroite, enemyPos);
			target = basDroite;
			angle = angle + M_PI;
		}
		if (enemyPos.x <= basDroite.x && enemyPos.y >= basDroite.y && target == basDroite)
		{
			choixCible(hautGauche, enemyPos);
			target = hautGauche;
			angle = angle + M_PI;
		}

		setPosition(enemyPos.x + (cos(angle) * vitesse), enemyPos.y + (sin(angle) * vitesse));
	}
}

/// <summary>
/// Choisis la cible selon la position de la cible et l'enemy
/// </summary>
/// <param name="posCible">The position cible.</param>
/// <param name="enemy">The enemy.</param>
void Enemy4::choixCible(Vector2f posCible, Vector2f enemy)
{
	//Gestion de l'angle
	angle = (atanf((posCible.y - enemy.y) / (posCible.x - enemy.x)));
}


