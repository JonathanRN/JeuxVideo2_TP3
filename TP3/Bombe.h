#pragma once
#include "Bonus.h"
namespace tp3
{
	class Bombe : public Bonus
	{
	public:
		Bombe(Vector2f position, Texture& texture);
		Color choixCouleur();
		void anim();
		void initGraphiques();
		~Bombe();
	private:
		static const int NOMBRES_ANIM = 13;
		static const int RHYTME_ANIM = 6;
		int animation = 0;
		const int ANIMATION_MAXIMALE = 100;
		int image;
		IntRect rectangleAnimation;
	};
}

