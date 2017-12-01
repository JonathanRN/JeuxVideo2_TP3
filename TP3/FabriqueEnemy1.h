#pragma once
#include "FabriqueEnemy.h"
#include "Enemy1.h"


namespace tp3
{
	class FabriqueEnemy1 : public FabriqueEnemy
	{
	public:
		Enemy* fabriquerEnemy(Texture &texture, Color color, int num)
		{
			return new Enemy1(getPosition(), texture, color, num);
		}
	};
}