#pragma once
#include "Bonus.h"
namespace tp3
{
	class BombeElectro : public Bonus
	{
	public:
		BombeElectro(Vector2f position, Texture& texture);
		Color choixCouleur();
		~BombeElectro();
	};
}

