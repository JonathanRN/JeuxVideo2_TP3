#pragma once
#include <vector>
#include <sstream>
#include "FondMobile.h"
#include "Scene.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include "Projectile_normal.h"
#include "Projectile_Enemy.h"
#include "Bonus.h"
#include "BonusShield.h"
#include "BombeElectro.h"
#include "Shield.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Pile.h"
#include "File.h"
#include "FabriqueEnemy1.h"
#include "Portail.h"

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
		void chargerNiveau(const int niveau);
		void animText();
		void animPortail(Enemy* temp);

		static const int NBR_PROJ = 100;
		static const int NBR_BONUS = 5;
		static const int NBR_ENEMY = 10;
		static const int NBR_PORTAIL = 6;
		int thrust;
		int fabriqueActive = 0;
		int niveauActif;

		int nbEnemy1 = 0;
		int nbEnemy2 = 0;
		int nbEnemy3 = 0;
		int nbEnemy4 = 0;

		Clock clock_tirer;
		Clock clock_pivoter;
		Clock clock_tire_enemy2;
		Clock spawnEnemy;
		Clock animationText;

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
		FabriqueEnemy* fabriqueEnemy1 = new FabriqueEnemy1();
		FabriqueEnemy* fabriqueEnemy2 = new FabriqueEnemy1();
		FabriqueEnemy* fabriqueEnemy3 = new FabriqueEnemy1();
		FabriqueEnemy* fabriqueEnemy4 = new FabriqueEnemy1();
		FabriqueEnemy* fabriqueEnemy5 = new FabriqueEnemy1();
		FabriqueEnemy* fabriqueEnemy6 = new FabriqueEnemy1();
		Texture portailT;
		Portail* portail[6];

		FondMobile fond;
	
		Font font;
		Text textNiveau;
		std::ostringstream text;
		bool textAfficheTerminer;
	};
}

