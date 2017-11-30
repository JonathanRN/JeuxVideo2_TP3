#pragma once
#include "Enemy.h"

namespace tp3
{
	class FabriqueEnemy
	{
	public:
		virtual Enemy* fabriquerEnemy(Vector2f position, Texture &texture, Color color) = 0;
	};
}
