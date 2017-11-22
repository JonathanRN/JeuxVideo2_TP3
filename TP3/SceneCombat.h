#pragma once
#include "FondMobile.h"
#include "Scene.h"

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
		FondMobile fond;
		Font font;
		Text testText;
	};
}

