#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "IObservateur.h"
#include <iostream>
#include "Bonus.h"
#include "Bombe.h"
#include <random>
#include <time.h>
#include "Vaisseau.h"

using namespace sf;

namespace tp3
{
	class Enemy : public Sprite , public IObservateur
	{
	public:
		void initExplosion();
		Enemy(Vector2f position, Texture &texture, Color color, int numFabrique);
		~Enemy();
		void animExplosion();
		virtual void action(Vaisseau& cible);
		void notifier(Sujet* sujet);

		int dommageCollision;
		int dommageTir;
		int ptsVie;
		int direction;
<<<<<<< HEAD
		int numeroFabrique;
=======
		bool canShoot = true;
>>>>>>> df0cc7792e09020afd2e2eff306a3586cf42f0d1
		bool isReady;

	protected:
		const int LARGEUR = 1280;
		const int HAUTEUR = 720;
		int vitesse;
		int posX; //Position X avant de commencer l'action
		static const int RHYTME_ANIM = 4;
		int animation;
		const int ANIMATION_MAXIMALE = 100; //A MODIFER, NOMBRE DANIMS * 10
		bool actif;
		int image;
		IntRect rectangleAnimation;
	};
}