#pragma once
#include "Bonus.h"
namespace tp3
{
	class BonusLaserBeam : public Bonus
	{
	public:
		BonusLaserBeam(Vector2f position, Texture& texture);
		~BonusLaserBeam();
	};
}


