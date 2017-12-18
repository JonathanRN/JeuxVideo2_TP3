#pragma once
#include "Bonus.h"
namespace tp3
{
	class BombeElectro : public Bonus
	{
	public:
		BombeElectro(Vector2f position, Texture& texture);
		Color choixCouleur();
		void anim();
		void initGraphiques();
		~BombeElectro();

	private:
		static const int NOMBRES_ANIM = 4;
		static const int RHYTME_ANIM = 6;
		int animation; //Animation présente
		const int ANIMATION_MAXIMALE = 100;
		int image; //Image présente
		IntRect rectangleAnimation; //Rectange d'animation
	};
}

