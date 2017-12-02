#pragma once
#include "Scene.h"
#include "FondMobile.h"
#include <sstream>
#include <iostream>

namespace tp3
{
	class SceneTitre : public Scene
	{
	public:
		SceneTitre();
		~SceneTitre();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		// Vecteur qui détermine la position de la souris à l'écran
		Vector2i pixelPos;
		Vector2f worldPos;

		FondMobile fond;
		Font font;
		Text titre;
		Text jouer;
		Text quitter;
		Text description1;
		Text description2;
		Text description3;
		char titreText[14] = { 'S','h','i','p','\'','s','\ ','n','o','t','\ ','h','o','t' };
		std::ostringstream text;
		bool animTitreFinie = false;

		Sprite vaisseau;
		Texture vaisseauT;
		bool animVaisseauFinie = false;
	};
}

