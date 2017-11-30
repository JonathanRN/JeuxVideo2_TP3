#pragma once
#include "FabriqueEnemy.h"
#include "Enemy1.h"


namespace tp3
{
	class FabriqueEnemy1 : public FabriqueEnemy
	{
	public:
		Enemy* fabriquerEnemy(Vector2f position, Texture &texture, Color color)
		{
			return new Enemy1(position, texture, color);
		}
	};
}