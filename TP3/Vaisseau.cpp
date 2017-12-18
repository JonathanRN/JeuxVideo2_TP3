#include "Vaisseau.h"

using namespace tp3;

Vaisseau::Vaisseau() : image(CENTRE)
{
	isPivoting = false;
	weapon = Base;
	weapons.push_back(new Weapon(Base));

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
//// <summary>
/// Réaction aux bonus
/// </summary>
/// <param name="sujet">The sujet.</param>
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
				if (distance < 200)
				{
					ptsVie -= 2;
				}
			}
		}
		else
		{
			int distance = sqrt(pow(bombe->getPosition().x - this->getPosition().x, 2) + pow(bombe->getPosition().y - this->getPosition().y, 2));
			if (distance < 200)
			{
				ptsVie -= 2;
			}		
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
			weapons.push_back(new Weapon(Scatter));
			haveScatter = true;
			positionWeapon++;
		}
		munitionScatter += 150;
	}
	if (typeid(*sujet) == typeid(BonusLaserBeam))
	{
		if (haveLaser == false)
		{
			weapons.push_back(new Weapon(FatLaser));
			haveLaser = true;
			positionWeapon++;
		}
		munitionLaserbeam += 2;
	}
	if (typeid(*sujet) == typeid(BonusMissile))
	{
		if (haveMissile == false)
		{
			weapons.push_back(new Weapon(Missile));
			haveMissile = true;
			positionWeapon++;
		}
		munitionMissile += 50;
	}

}

//ANIMATION DE LA DESCENTE DU VAISSEAU
void Vaisseau::descendre()
{
	if (image < LIMITE_BAS && isPivoting == false)
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
	if (image > LIMITE_HAUT && isPivoting == false)
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
/// <summary>
/// Fait pivoter le vaisseau en x
/// </summary>
void Vaisseau::pivoter()
{
	if (!isPivoting)
	{
		image = LIMITE_GAUCHE_PIVOT;
		isPivoting = true;
	}

	if(image != LIMITE_DROITE_PIVOT)
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
		rectangleAnimation.left = (rectangleAnimation.width + OFFSET) * (image / RHYTME_ANIM);
		setScale(getScale().x * -1, getScale().y);
		direction *= -1;
		setTextureRect(rectangleAnimation);
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