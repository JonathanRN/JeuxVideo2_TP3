#pragma once
#include "Bonus.h"
namespace tp3
{
	class Bombe : public Bonus
	{
	public:
		Bombe(Vector2f position, Texture& texture);
		Color choixCouleur();
		~Bombe();
	};
}

