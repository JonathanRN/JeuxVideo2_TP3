#pragma once

#include "VaisseauLogique.h"
#include <vector>
#include <iostream>
#include "Bonus.h"
#include "Weapon.h"
#include "BonusScatter.h"
#include "BonusShield.h"
#include "BonusLaserBeam.h"
#include "BonusMissile.h"
#include "Bombe.h"
#include "BombeElectro.h"
#include "Shield.h"
#include "list.h"
#include "Pile.h"
#include "IObservateur.h"
namespace tp3
{
	class Vaisseau : public VaisseauLogique , public IObservateur
	{
	public:
		Vaisseau();
		virtual ~Vaisseau();
		virtual void mouvement(int thrust);
		virtual void mouvementJoueur(Vector2i& mouvement);
		void notifier(Sujet* sujet);
		void monter();
		void descendre();
		void centrer();
		void pivoter();
		virtual void initGraphiques();

		int direction = 1;
		int ptsVie = 10;

		Texture shield;
		Pile<Shield*> shields;

		bool canShoot = true;
		bool haveLaser = false;
		bool haveScatter = false;
		bool haveMissile = false;
		bool isPivoting;

		int munitionMissile = 0;
		int munitionScatter = 0;
		int munitionLaserbeam = 0;

		std::vector<Weapon*> weapons;
		int positionWeapon = 0;
		Weapon weapon;
	private:
		static const int OFFSET = 0;
		static const int CENTRE = 24;
		static const int LIMITE_DROITE_PIVOT = 74;
		static const int LIMITE_GAUCHE_PIVOT = 54;
		static const int LIMITE_BAS = 49;
		static const int LIMITE_HAUT = 0;
		static const int RHYTME_ANIM = 10;


		
		

		int image;
		IntRect rectangleAnimation;
	};
}

