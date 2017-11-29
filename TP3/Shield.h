#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
namespace tp3
{
	class Shield : public Sprite
	{
	public:
		Shield(Vector2f position, Texture& texture);
		Color choixCouleur();
		~Shield();
		int ptsShield;
	private:
	};
}

