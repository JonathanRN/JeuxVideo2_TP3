#pragma once
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
		Enemy(Vector2f position);
		~Enemy();
		virtual void action() = 0;
	};
}