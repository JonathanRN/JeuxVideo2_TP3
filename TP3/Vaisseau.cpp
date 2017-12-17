#include "Vaisseau.h"

using namespace tp3;

Vaisseau::Vaisseau() : image(CENTRE)
{
	isPivoting = false;
	weapon = Base;
}


Vaisseau::~Vaisseau()
{
	
}

//MOUVEMENT QUI SE DIRIGE TOUT SIMPLEMENT VERS LA GAUCHE
void Vaisseau::mouvement(int thrust)
{
	move(-VITESSE - thrust, 0);
}

//MOUVEMENT CONTRÔLÉ PAR LE JOUEUR
void Vaisseau::mouvementJoueur(Vector2i& mouvement)
{
	move(mouvement.x * VITESSE, mouvement.y * VITESSE);
}

void Vaisseau::notifier(Sujet * sujet)
{
	if (typeid(*sujet) == typeid(BonusShield))
	{
		shields.push(new Shield(getPosition(), shield));
	}
	if (typeid(*sujet) == typeid(Bombe))
	{
		Bombe* bombe = dynamic_cast<Bombe*>(sujet);
		if (!shields.empty())
		{
			if (bombe->getColor() != shields.top()->getColor())
			{
				int distance = sqrt(pow(bombe->getPosition().x - this->getPosition().x, 2) + pow(bombe->getPosition().y - this->getPosition().y, 2));
				ptsVie -= (750 - distance) / 20;
				std::cout << ((750 - distance) / 20) / 4 << std::endl;//couutt
			}
		}
		else
		{
			int distance = sqrt(pow(bombe->getPosition().x - this->getPosition().x, 2) + pow(bombe->getPosition().y - this->getPosition().y, 2));
			ptsVie -= ((750 - distance) / 20)/10;
			std::cout << ((750 - distance) / 20) / 4 << std::endl;//couuttt
			
		}
	}
	if (typeid(*sujet) == typeid(BombeElectro))
	{
		canShoot = false;
	}
	if (typeid(*sujet) == typeid(BonusScatter))
	{
		if (haveScatter == false)
		{
			weapons.push_back(Scatter);
			haveScatter = true;
		}
		munitionScatter += 250;
	}
	if (typeid(*sujet) == typeid(BonusLaserBeam))
	{
		if (haveLaser == false)
		{
			weapons.push_back(FatLaser);
			haveLaser = true;
		}
		munitionLaserbeam += 2;
	}

}

//ANIMATION DE LA DESCENTE DU VAISSEAU
void Vaisseau::descendre()
{
	if (image < LIMITE_BAS)
	{
		image++;

		if (image % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left = (rectangleAnimation.width + OFFSET) * (image / RHYTME_ANIM);
			setTextureRect(rectangleAnimation);
		}
	}
}

//ANIMATION DE LA MONTÉE DU VAISSEAU
void Vaisseau::monter()
{
	if (image > LIMITE_HAUT)
	{
		image--;

		if (image % RHYTME_ANIM == 9)
		{
			rectangleAnimation.left = (rectangleAnimation.width + OFFSET) * (image / RHYTME_ANIM);
			setTextureRect(rectangleAnimation);
		}
	}
}

//SI ON EST PAS EXACTEMENT AU CENTRE, ON RAMÈNE LE VAISSEAU AU CENTRE
void Vaisseau::centrer()
{
	if (!isPivoting)
	{
		if (image == CENTRE)
			return;

		if (image < CENTRE)
		{
			descendre();
		}
		else if (image > CENTRE)
		{
			monter();
		}
	}
}

void Vaisseau::pivoter()
{
	if (!isPivoting)
	{
		image = LIMITE_GAUCHE_PIVOT;
		isPivoting = true;
	}

	while (image != LIMITE_DROITE_PIVOT)
	{
		image++;
		if (image % RHYTME_ANIM == 0)
		{
			rectangleAnimation.left = (rectangleAnimation.width + OFFSET) * (image / RHYTME_ANIM);
 			setTextureRect(rectangleAnimation);
		}
	}

	if (image == LIMITE_DROITE_PIVOT)
	{
 		isPivoting = false;
		image = CENTRE;
		setScale(getScale().x * -1, getScale().y);
		direction *= -1;
	}
}

void Vaisseau::initGraphiques()
{
	rectangleAnimation.width = (getTextureRect().width / 11) - OFFSET;
	rectangleAnimation.height = getTextureRect().height;
	rectangleAnimation.top = 0;
	rectangleAnimation.left = (rectangleAnimation.width + OFFSET) * (image / RHYTME_ANIM);
	setTextureRect(rectangleAnimation);

	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}