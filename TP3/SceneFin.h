#pragma once
#include "Scene.h"
#include "FondMobile.h"
#include <sstream>
#include <iostream>

namespace tp3
{
	class SceneFin : public Scene
	{
	public:
		SceneFin();
		~SceneFin();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		// Vecteur qui détermine la position de la souris à l'écran
		Vector2i pixelPos;
		Vector2f worldPos;

		Text gameOver;
		Text scoreText;
		Text quitter;
		Text score;

		FondMobile fond;
		Font font;
	};
}

