#pragma once
#include "VaisseauLogique.h"
#include <vector>
#include <iostream>

namespace tp3
{
	class Vaisseau : public VaisseauLogique
	{
	public:
		Vaisseau();
		virtual ~Vaisseau();
		virtual void mouvement(int thrust);
		virtual void mouvementJoueur(Vector2i& mouvement);

		void monter();
		void descendre();
		void centrer();
		void pivoter();
		int direction = 1;
		virtual void initGraphiques();

	private:
		static const int OFFSET = 0;
		static const int CENTRE = 24;
		static const int LIMITE_DROITE_PIVOT = 74;
		static const int LIMITE_GAUCHE_PIVOT = 54;
		static const int LIMITE_BAS = 49;
		static const int LIMITE_HAUT = 0;
		static const int RHYTME_ANIM = 10;

		
		bool isPivoting;

		int image;
		IntRect rectangleAnimation;
	};
}

