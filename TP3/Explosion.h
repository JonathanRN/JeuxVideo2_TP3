#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

namespace tp3
{
	class Explosion : public Sprite
	{
	public:
		Explosion(Vector2f position, Texture& texture);
		~Explosion();
		void anim();
		void initGraphiques();
		bool animTermine = false;
		bool isReady = false;
	private:
		static const int NOMBRES_ANIM = 16;
		static const int RHYTME_ANIM = 6;
		int animation = 0;
		const int ANIMATION_MAXIMALE = 100;
		int image;
		IntRect rectangleAnimation;
	};
}

