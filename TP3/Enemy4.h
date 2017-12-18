#pragma once
#include "Enemy.h"
#include "Projectile_Enemy.h"

namespace tp3
{
	class Enemy4 : public Enemy
	{
	public:
		Enemy4(Vector2f position, Texture &texture, Color color, int num);
		~Enemy4();

	private:
		void action(Vaisseau &cible);
		void choixCible(Vector2f posCible, Vector2f enemy);
		float angle;

		//4 cibles dans le jeu pouvant être ciblées par l'ennemis 4
		Vector2f hautGauche = Vector2f(100, 100);
		Vector2f basGauche = Vector2f(100, HAUTEUR - 100);
		Vector2f hautDroite = Vector2f(LARGEUR - 100, 100);
		Vector2f basDroite = Vector2f(LARGEUR - 100, HAUTEUR - 100);

		//Par défaut, la première cible est en haut a gauche
		Vector2f target = hautGauche;
	};
}

