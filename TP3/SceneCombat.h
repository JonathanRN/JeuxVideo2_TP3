#pragma once
#include <vector>
#include "FondMobile.h"
#include "Scene.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include "Projectile_normal.h"
#include "Bonus.h"
#include "BonusShield.h"
#include "Shield.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"

using namespace std;
namespace tp3
{
	class SceneCombat : public Scene
	{
	public:
		SceneCombat();
		~SceneCombat();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
		Color choixCouleur();
		void ajouterProjectile(Vector2f position);

	private:
		void collisionProjectilesEnnemis();
		void collisionVaisseauEnnemis();
		void gererBoucliers();
		void gererProjectiles();
		void gererEnnemis();
		void gererBonus();

		static const int NBR_PROJ = 100;
		static const int NBR_BONUS = 5;
		static const int NBR_ENEMY = 10;
		int thrust;

		Clock clock_tirer;
		Clock clock_pivoter;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
		Texture ennemisT[3];
		Enemy* ennemis[NBR_ENEMY];

		Texture player;
		Projectile* projectiles[NBR_PROJ];
		Bonus* bonus[NBR_BONUS];
		Texture projectileT[5];
		Texture shield;
		Texture bonusT[5];
		
		vector<Shield*> shields;
		FondMobile fond;
	
		Text testText;
	};
}

