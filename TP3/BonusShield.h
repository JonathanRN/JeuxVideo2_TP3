#pragma once
#include "Bonus.h"
namespace tp3
{
	class BonusShield : public Bonus
	{
	public:
		BonusShield(Vector2f position,Texture& texture);
		~BonusShield();
	};
}

