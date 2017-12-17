#pragma once
#include "Enemy.h"
namespace tp3
{
	class Boss : public Enemy
	{
	public:
		Boss(Vector2f position, Texture &texture, Color color, int num);
		~Boss();

	private:
		void action(Vaisseau &cible);
		int directionY;
		int phase = 1;
		bool isReadyPhase3 = false;
	};
}

