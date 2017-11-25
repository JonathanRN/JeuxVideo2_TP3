#pragma once
#include "Enemy.h"
#include "Vaisseau.h"

namespace tp3
{
	class Enemy1 : public Enemy
	{
	public:
		Enemy1(Vector2f position, Texture &texture);
		~Enemy1();

	private:
		void action(Vaisseau& cible);

		float angle;
	};
}

