#pragma once
#include <vector>
#include "FondMobile.h"
#include "Scene.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include "Projectile_normal.h"

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
		int thrust;

		Clock clock_tirer;
		Clock clock_pivoter;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
		Texture player;
		Projectile* projectiles[NBR_PROJ];
		Texture projectileT[5];

		FondMobile fond;
	
		Text testText;
	};
}

