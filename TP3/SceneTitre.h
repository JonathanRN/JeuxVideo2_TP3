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
		FondMobile fond;
		Font font;
		Text titre;
		char titreText[6] = { 'C','a','n','c','e','r' };
		std::ostringstream text;

		Sprite vaisseau;
		Texture vaisseauT;
		bool animVaisseauFinie = false;
	};
}

