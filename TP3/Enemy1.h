#pragma once
#include "Enemy.h"
#include "Vaisseau.h"

namespace tp3
{
	class Enemy1 : public Enemy
	{
	public:
		Enemy1(Vector2f position);
		~Enemy1();
		void action(Vaisseau& cible);
	};
}

