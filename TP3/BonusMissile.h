#pragma once
#include "Bonus.h"
namespace tp3
{
	class BonusMissile : public Bonus
	{
	public:
		BonusMissile(Vector2f position, Texture& texture);
		~BonusMissile();
	};
}

