#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <sstream>
#include "BonusScatter.h"
#include "FondMobile.h"
#include "Scene.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include "Projectile_normal.h"
#include "Projectile_Beam.h"
#include "Projectile_Missile.h"
#include "Weapon.h"
#include "Projectile_Enemy.h"
#include "Bonus.h"
#include "BonusShield.h"
#include "BonusLaserBeam.h"
#include "BonusMissile.h"
#include "BombeElectro.h"
#include "Shield.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Boss.h"
#include "Pile.h"
#include "File.h"
#include "FabriqueEnemy1.h"
#include "Portail.h"
#include "Boss_Groupe.h"
#include "Enemy_Boss.h"

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
		void ajouterProjectileEnnemis(Vector2f position, Color color, int direction, float scale, float angle);

	private:
		void addObserver();
		void gererExplo();
		void collisionProjectilesEnnemis();
		void collisionVaisseauEnnemis();
		void gererBoucliers();
		void gererWeapons();
		void gererProjectiles();
		void gererListeEnnemisHUD();
		void gererEnnemis();
		void gererNiveauBoss();
		void gererBonus();
		void gererScoreJoueur();
		void nbEnnemis();
		void chargerNiveau(const int niveau);
		void animText();

		static const int NBR_PROJ = 100;
		static const int NBR_BONUS = 5;
		static const int NBR_ENEMY = 10;
		static const int NBR_PORTAIL = 6;
		int thrust;
		int fabriqueActive = 0;
		int niveauActif;
		int scoreJoueur = 0;

		int nbEnemy1 = 0;
		int nbEnemy2 = 0;
		int nbEnemy3 = 0;
		int nbEnemy4 = 0;
		bool dernierNiveau = false;
		bool peutCreerEnnemi = true;

		Clock clock_tirer;
		Clock clock_pivoter;
		Clock clock_tire_enemy2;
		Clock clock_tire_enemy3;
		Clock clock_tire_enemy4;
		Clock clock_tire_boss;
		Clock spawnEnemy;
		Clock spawnEnemy_boss;
		Clock animationText;
		Clock tempsBombeElectro;
		Clock tempsBombeElectroEnnemis;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
		Texture ennemisT[4];
		Texture bossT;
		std::vector<Enemy*> ennemis;
		std::vector<Enemy_Boss*> ennemisBoss;
		Boss_Groupe grp;

		Texture player;
		Projectile* projectiles[NBR_PROJ];
		Projectile_Enemy* projectilesEnemy[NBR_PROJ];
		Bonus* bonus[NBR_BONUS];
		Texture projectileT[5];
		Texture projectileEnemy;
		
		Texture bonusT[7];
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
	
		CircleShape explo = CircleShape(0, 30);
		bool readyExplo = false;
		Font font;
		Text textNiveau;
		std::ostringstream text;
		bool textAfficheTerminer;

		//Section HUD
		Texture hudT;
		Texture iconBouclier;
		Sprite hud;
		Text niveauTextHUD;
		Text niveauHUD;
		Text scoreHUD;
		Text munitionsHUD;
		Text ptsVieText;
		Text ptsBouclier;
		static const int NB_BARRES_VIES = 10;
		RectangleShape* barresVie[NB_BARRES_VIES];

		static const int NB_BARRES_BOUCLIERS = 5;
		vector<RectangleShape*> barresBouclier;

		static const int NB_BARRES_ENNEMIS = 7;
		vector<RectangleShape*> barresEnnemis;
		Texture enemyListeT[4];
	};
}

