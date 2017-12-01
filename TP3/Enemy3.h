#pragma once
#include "Enemy.h"
namespace tp3
{
	class Enemy3 : public Enemy
	{
	public:
		Enemy3(Vector2f position, Texture &texture, Color color, int num);
		~Enemy3();

	private:
		void action(Vaisseau &cible);
		int directionY;
	};
}
