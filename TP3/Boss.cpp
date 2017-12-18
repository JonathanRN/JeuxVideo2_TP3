#include "Boss.h"
using namespace tp3;


Boss::Boss(Vector2f position, Texture &texture, Color color, int num) :Enemy(position, texture, color, num)
{
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	dommageCollision = 4;
	dommageTir = 1;
	vitesse = 0.5f;
	ptsVie = 600;
	direction = -1;
	directionY = 1;
	isReady = false;
	posX = 60;
	grosseur = 5;
}


Boss::~Boss()
{
}

/// <summary>
/// Méthode bouger du composite
/// </summary>
void tp3::Boss::bouger()
{
	float enemyX = getPosition().x;
	float enemyY = getPosition().y;

	if (!isReady)
	{
		move(direction*vitesse, 0);
		if (direction == 1 && getPosition().x > LARGEUR + 230)
		{
			setPosition(-230, HAUTEUR / 2); //Il change de cote
			isReadyPhase3 = true;
		}
		else if (direction == 1 && getPosition().x > posX && isReadyPhase3)
		{
			isReady = true;
		}
	}
	if (isReady)
	{
		//Fais bouger les ennemis selon les limites de l'ecran
		if (enemyY - getTexture()->getSize().y / 2 < 0)
		{
			directionY = 1;
		}
		else if (enemyY + getTexture()->getSize().y / 2 > 720)
		{
			directionY = -1;
		}
		move(0, directionY * vitesse);
		rotate(0.8 * vitesse);
	}
}

/// <summary>
/// Méthode arreter du composite
/// </summary>
void tp3::Boss::arreter()
{
	rotate(0.8 * vitesse);
}

/// <summary>
/// Méthode action qui se fait à chaque update 
/// </summary>
/// <param name="cible">The cible.</param>
void Boss::action(Vaisseau & cible)
{
	float enemyX = getPosition().x;
	float enemyY = getPosition().y;

	//Phase 1
	if (phase == 1)
	{
		if (!isReady)
		{
			move(direction*vitesse, 0);
			if (direction == -1 && getPosition().x < LARGEUR - posX)
			{
				isReady = true;
			}
		}

		if (isReady)
		{
			//Fais bouger les ennemis selon les limites de l'ecran
			if (enemyY - getTexture()->getSize().y / 2 < 0)
			{
				directionY = 1;
			}
			else if (enemyY + getTexture()->getSize().y / 2 > 720)
			{
				directionY = -1;
			}
			move(0, directionY * vitesse);
			rotate(0.8 * vitesse);
		}
		//Si le boss perd le tier de sa vie
		if (ptsVie <= 400)
		{
			phase = 2; //On va a la prochaine phase
		}
	}
	//Phase 2
	else if (phase == 2)
	{
		if (ptsVie <= 200)
		{
			phase = 3;
			isReady = false;
			ptsVie += 100; //Lui remet un peu de points de vies ;)
			vitesse = 1.2f; //Il va plus vite
			direction *= -1; //Change la direction
		}
	}
}
