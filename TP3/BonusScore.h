#pragma once
#include "Bonus.h"
namespace tp3
{
	class BonusScore : public Bonus
	{
	public:
		BonusScore(Vector2f position, Texture& texture);
		~BonusScore();
	};
}
