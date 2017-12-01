#pragma once
#include "Enemy.h"

namespace tp3
{
	class Enemy1 : public Enemy
	{
	public:
		Enemy1(Vector2f position, Texture &texture, Color color, int numFabrique);
		~Enemy1();

	private:
		void action(Vaisseau& cible);
		float angle;
	};
}

