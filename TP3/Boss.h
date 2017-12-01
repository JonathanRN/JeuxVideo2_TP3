#pragma once
#include "Enemy.h"
namespace tp3
{
	class Boss : public Enemy
	{
	public:
		Boss(Vector2f position, Texture &texture, Color color, int num);
		~Boss();
	};
}

