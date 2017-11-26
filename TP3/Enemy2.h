#pragma once
#include "Enemy.h"
namespace tp3
{
	class Enemy2 : public Enemy
	{
	public:
		Enemy2(Vector2f position, Texture &texture, Color color);
		~Enemy2();

	private:
		void action(Vaisseau &cible);
		int directionY;
	};
}

