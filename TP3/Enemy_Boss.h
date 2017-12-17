#pragma once
#include "Enemy.h"
#include "IComponant.h"

namespace tp3
{
	class Enemy_Boss : public Enemy
	{
	public:
		Enemy_Boss(Vector2f position, Texture &texture, Color color, int num);
		~Enemy_Boss();

	private:
		virtual void bouger();
		virtual void arreter();
		void action(Vaisseau &cible);
		int directionY;
	};
}
