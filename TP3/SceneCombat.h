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
#include "BonusScore.h"
#include "Explosion.h"
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
		void ajouterScore(int indexEnnemis);
		void nbEnnemis();
		void chargerNiveau(int niveau);
		void animText();
		void gererFinJeu();

		static const int NBR_PROJ = 100;
		static const int NBR_BONUS = 5;
		static const int NBR_ENEMY = 10;
		static const int NBR_PORTAIL = 6;
		int thrust; //vitesse fond moblile
		int fabriqueActive = 0;
		int niveauActif;
		//int scoreJoueur = 0;

		int nbEnemy1 = 0;
		int nbEnemy2 = 0;
		int nbEnemy3 = 0;
		int nbEnemy4 = 0;
		int nbEnemyBoss = 0;
		bool dernierNiveau = false;
		bool peutCreerEnnemi = true;
		bool peutCreerEnnemi2 = true;
		bool bonusScoreActif = false;
		bool peutSwitchWeapon = true;
		bool debugMode = false;
		bool jeuTermine = false;

		Clock clock_tirer;
		Clock clock_pivoter;
		Clock clock_tire_enemy2;
		Clock clock_tire_enemy3;
		Clock clock_tire_enemy4;
		Clock clock_tire_boss;
		Clock clock_tire_enemyBoss;
		Clock spawnEnemy;
		Clock animationText;
		Clock tempsBombeElectro;
		Clock tempsBombeElectroEnnemis;
		Clock tempsBonusScore;
		Clock tempsSwitchWeapon;
		Clock animationWarning;
		Clock clock_finDeJeu;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
		Texture ennemisT[4];
		Texture bossT;
		CircleShape* cercleCollision;
		std::vector<Enemy*> ennemis;
		std::vector<Explosion*> explosions;
		Texture explosionT;
		Boss_Groupe grp;

		Texture player;
		Projectile* projectiles[NBR_PROJ];
		Projectile_Enemy* projectilesEnemy[NBR_PROJ];
		Bonus* bonus[NBR_BONUS];
		Texture projectileT[5];
		Texture projectileEnemy;
		
		Texture bonusT[7];
		
		
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
		Text warning;
		Text textBoss;
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

		static const int NB_BARRES_VIES_BOSS = 12;
		RectangleShape* barresViesBoss[NB_BARRES_VIES_BOSS];

		static const int NB_BARRES_BOUCLIERS = 5;
		vector<RectangleShape*> barresBouclier;

		static const int NB_BARRES_ENNEMIS = 7;
		vector<RectangleShape*> barresEnnemis;
		Texture enemyListeT[4];

		static const int NB_BARRES_ARMES = 4;
		RectangleShape* barresArmes[NB_BARRES_ARMES];
		Texture iconArmes[4];
	};
}

