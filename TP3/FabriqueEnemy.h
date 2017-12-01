#pragma once
#include "Enemy.h"

namespace tp3
{
	class FabriqueEnemy : public Sprite
	{
	public:
		virtual Enemy* fabriquerEnemy(Texture &texture, Color color, int num) = 0;
	};
}
