#include "Enemy4.h"

using namespace tp3;

Enemy4::Enemy4(Vector2f position, Texture &texture, Color color, int num) :Enemy(position, texture, color, num)
{
	setScale(getScale().x * -0.8, getScale().y * 0.8);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 4;
	dommageTir = 1;
	vitesse = 8;
	ptsVie = 5;
	direction = 1;
	isReady = false;
	posX = 90;
}


Enemy4::~Enemy4()
{
}

void Enemy4::action(Vaisseau &cible)
{
	Vector2f hautGauche = Vector2f( 100, 100 );
	Vector2f basGauche = Vector2f( 100, HAUTEUR - 100 );
	Vector2f hautDroite = Vector2f( LARGEUR - 100, 100 );
	Vector2f basDroite = Vector2f( LARGEUR - 100, HAUTEUR - 100 );
	Vector2f enemyPos = getPosition();

	//if (!isReady)
	{
		/*move(-direction*vitesse, 0);
		if (direction == -1 && getPosition().x > posX)
		{
			isReady = true;
		}
		else if (direction == 1 && getPosition().x < LARGEUR - posX)
		{
			isReady = true;
		}*/

		//if (enemyPos != hautGauche && enemyPos != hautDroite && enemyPos != basGauche && enemyPos != basDroite) //Si ennemi n'a pas commence sa boucle
		//{
		//	//Il la commence
		//	choixCible(hautGauche, enemyPos);
		//}
	}
	//else
	{	
		if (enemyPos.x >= hautGauche.x && enemyPos.y >= hautGauche.y)
		{
			choixCible(basGauche, enemyPos);
		}
		if (enemyPos.x >= basGauche.x && enemyPos.y >= basGauche.y)
		{
			choixCible(hautDroite, enemyPos);
		}
		if (enemyPos.x >= hautDroite.x && enemyPos.y >= hautDroite.y)
		{
			choixCible(basDroite, enemyPos);
		}
		if (enemyPos.x >= basDroite.x && enemyPos.y >= basDroite.y)
		{
			choixCible(hautGauche, enemyPos);
		}

		setPosition(enemyPos.x + (cos(angle) * vitesse), enemyPos.y + (sin(angle) * vitesse));
	}
}

void Enemy4::choixCible(Vector2f posCible, Vector2f enemy)
{
	//Gestion de l'angle
	angle = (atanf((posCible.y - enemy.y) / (posCible.x - enemy.x)));

	/*if (posCible.x < enemy.x)
	{
		angle = angle + M_PI;
	}*/
}


