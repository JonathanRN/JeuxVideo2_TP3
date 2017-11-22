#pragma once
#include "FondMobile.h"
#include "Scene.h"
#include "Vaisseau.h"

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

	private:
		int thrust;

		Vaisseau vaisseauJoueur;
		Vector2i mouvementJoueur;
		Texture Player_up_down;
		Texture Player_pivot;
		Texture death;


		FondMobile fond;
		Font font;
		Text testText;
	};
}

