#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

namespace tp3
{
	class Portail : public Sprite
	{
	public:
		Portail(Vector2f position, Texture& texture);
		~Portail();
		void anim();
		void initGraphiques();
	private:
		static const int NOMBRES_ANIM = 10;
		static const int RHYTME_ANIM = 4;
		int animation;
		const int ANIMATION_MAXIMALE = 100;
		int image;
		IntRect rectangleAnimation;
	};
}

