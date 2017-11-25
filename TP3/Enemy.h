#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
using namespace sf;

namespace tp3
{
	class Enemy : public Sprite
	{
	public:
		Color choixCouleur();
		Enemy(Vector2f position, Texture &texture);
		~Enemy();

	protected:
		const int VITESSE = 5;
	};
}