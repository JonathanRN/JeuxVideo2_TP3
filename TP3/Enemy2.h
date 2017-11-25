#pragma once
#include "Enemy.h"
namespace tp3
{
	class Enemy2 : public Enemy
	{
	public:
		Enemy2(Vector2f position, Texture &texture);
		~Enemy2();
	};
}

