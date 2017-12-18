#pragma once
#include "Enemy.h"
#include "IComponant.h"

namespace tp3
{
	class Boss : public Enemy
	{
	public:
		Boss(Vector2f position, Texture &texture, Color color, int num);
		~Boss();

	private:
		virtual void bouger();
		virtual void arreter();
		void action(Vaisseau &cible);
		int directionY; //DirectionY
		bool isReadyPhase3 = false; //Si le boss est prêt pour la phase 3
	};
}

