#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include "Vaisseau.h"

using namespace sf;

namespace tp3
{
	class Enemy : public Sprite
	{
	public:
		Enemy(Vector2f position, Texture &texture, Color color);
		~Enemy();
		virtual void action(Vaisseau& cible) = 0;

		int dommageCollision;
		int dommageTir;
		int ptsVie;

	protected:
		int vitesse;
		int direction;
	};
}