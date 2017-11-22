#pragma once
#include "Scene.h"

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
		Font font;
		Text testText;
	};
}

