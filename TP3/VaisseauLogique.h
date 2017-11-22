#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>

using namespace sf;

namespace tp3
{
	class VaisseauLogique : public Sprite
	{
	public:
		VaisseauLogique()
		{
		}

		virtual void mouvement(int thrust) = 0;
		virtual void mouvementJoueur(Vector2i& mouvement) = 0;

		virtual void initGraphiques() = 0;

	protected:
		static const int VITESSE = 5;
	};
}