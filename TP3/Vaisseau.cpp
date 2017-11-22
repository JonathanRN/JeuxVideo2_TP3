#include "Vaisseau.h"

using namespace tp3;

Vaisseau::Vaisseau() : image(CENTRE)
{
}


Vaisseau::~Vaisseau()
{
	
}

//MOUVEMENT QUI SE DIRIGE TOUT SIMPLEMENT VERS LA GAUCHE
void Vaisseau::mouvement(int thrust)
{
	move(-VITESSE - thrust, 0);

	mouvement(thrust);
}

//MOUVEMENT CONTRÔLÉ PAR LE JOUEUR
void Vaisseau::mouvementJoueur(Vector2i& mouvement)
{
	move(mouvement.x * VITESSE, mouvement.y * VITESSE);

	mouvementJoueur(mouvement);
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

void Vaisseau::pivoter()
{
}

void Vaisseau::initGraphiques()
{
	rectangleAnimation.width = (getTextureRect().width / 5) - OFFSET;
	rectangleAnimation.height = getTextureRect().height;
	rectangleAnimation.top = 0;
	rectangleAnimation.left = (rectangleAnimation.width + OFFSET) * (image / RHYTME_ANIM);
	setTextureRect(rectangleAnimation);

	setOrigin(rectangleAnimation.width / 2, rectangleAnimation.height / 2);
}