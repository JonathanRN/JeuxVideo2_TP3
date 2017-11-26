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
		void initExplosion();
		Enemy(Vector2f position, Texture &texture, Color color);
		~Enemy();
		void animExplosion();
		virtual void action(Vaisseau& cible) = 0;

		int dommageCollision;
		int dommageTir;
		int ptsVie;
		int direction;

	protected:
		int vitesse;
		

		static const int RHYTME_ANIM = 4;
		int animation;
		const int ANIMATION_MAXIMALE = 100; //A MODIFER, NOMBRE DANIMS * 10
		bool actif;
		int image;
		IntRect rectangleAnimation;
	};
}