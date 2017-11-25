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
		void ajouterProjectile(Vector2f position);


	private:
		static const int NBR_PROJ = 100;
		static const int NBR_BONUS = 5;
		int thrust;

		Clock clock_tirer;
		Clock clock_pivoter;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
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

