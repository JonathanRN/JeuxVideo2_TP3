#pragma once
#include "Bonus.h"
namespace tp3
{
	class BonusScatter : public Bonus
	{
	public:
		BonusScatter(Vector2f position, Texture& texture);
		~BonusScatter();
	};
}

