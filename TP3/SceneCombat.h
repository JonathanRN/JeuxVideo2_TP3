#pragma once
#include <vector>
#include "FondMobile.h"
#include "Scene.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include "Projectile_normal.h"
#include "Projectile_Enemy.h"
#include "Bonus.h"
#include "BonusShield.h"
#include "Shield.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Pile.h"
#include "File.h"

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
		void retObservateur(Enemy* observateur);
		void ajouterProjectile(Vector2f position);
		void ajouterBonus(Vector2f position);
		void ajouterProjectileEnnemis(Vector2f position, Color color, int direction);

	private:
		void collisionProjectilesEnnemis();
		void collisionVaisseauEnnemis();
		void gererBoucliers();
		void gererProjectiles();
		void gererEnnemis();
		void gererBonus();
		void nbEnnemis();
		void chargerNiveau(const int index);

		static const int NBR_PROJ = 100;
		static const int NBR_BONUS = 5;
		static const int NBR_ENEMY = 10;
		int thrust;

		int nbEnemy1 = 0;
		int nbEnemy2 = 0;
		int nbEnemy3 = 0;
		int nbEnemy4 = 0;

		Clock clock_tirer;
		Clock clock_pivoter;
		Clock clock_tire_enemy2;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
		Texture ennemisT[3];
		std::vector<Enemy*> ennemis;

		Texture player;
		Projectile* projectiles[NBR_PROJ];
		Projectile_Enemy* projectilesEnemy[NBR_PROJ];
		Bonus* bonus[NBR_BONUS];
		Texture projectileT[5];
		Texture projectileEnemy;
		
		Texture bonusT[5];
		Texture explosion;
		
		File<Enemy*> ennemisSuivants;

		FondMobile fond;
	
		Text testText;
	};
}

