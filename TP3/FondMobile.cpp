#include "FondMobile.h"
using namespace tp3;
FondMobile::FondMobile(const int largeur, const int hauteur, const int vitesse) : LARGEUR_ECRAN(largeur), HAUTEUR_ECRAN(hauteur), vitesse(vitesse)
{

}

/// <summary>
/// Sets the texture.
/// </summary>
/// <param name="path">The path.</param>
/// <returns></returns>
bool FondMobile::setTexture(const char * path)
{
	if (!fondEcranT.loadFromFile(path))
	{
		return false;
	}

	fondEcran.setTexture(fondEcranT);
	fondEcran.setPosition(0, 0);

	positions[0].x = 0.0f;
	positions[0].y = 0.0f;

	//SECONDE POSITION, JUSTE APRÈS LA FIN DE LA PREMIÈRE TAILLE DE TEXTURE
	positions[1].x = fondEcranT.getSize().x;
	positions[1].y = 0.0f;
}

/// <summary>
/// Bouge le fond mobile
/// </summary>
/// <param name="thrust">The thrust.</param>
void FondMobile::move(const int thrust)
{
	for (int i = 0; i < 2; i++)
	{
		positions[i].x -= vitesse + thrust;
		
		float temp = fondEcranT.getSize().x * -1.0f;

		//SI PLUS PETIT QUE LA TAILLE DE LA TEXTURE DE FOND, ON L'AVANCE DE DEUX FOIS CETTE TAILLE
		if (positions[i].x <= temp)
		{
			positions[i].x += fondEcranT.getSize().x * 2;
		}
	}
}

void FondMobile::draw(RenderWindow* rw)
{
	//UN SEUL SPRITE, IMPRIMÉ DEUX FOIS À DEUX POSITIONS DIFFÉRENTES.
	for (int i = 0; i < 2; i++)
	{
		fondEcran.setPosition(positions[i]);
		rw->draw(fondEcran);
	}
}

//VERSION AVEC DES RECTANGLES TAILLÉES, UN  PEU PLUS COMPLEXE

//FondMobile::FondMobile(const int largeur, const int hauteur, const int vitesse) : LARGEUR_ECRAN(largeur), HAUTEUR_ECRAN(hauteur), vitesse(vitesse)
//{
//	
//}
//
//
//bool FondMobile::setTexture(const char * path)
//{
//	if (!fondEcranT.loadFromFile(path))
//	{
//		return false;
//	}
//
//	fondEcran.setTexture(fondEcranT);
//	fondEcran.setPosition(0, 0);
//
//	rectPrincipal.width = LARGEUR_ECRAN;
//	rectPrincipal.height = HAUTEUR_ECRAN;
//	rectPrincipal.left = 0;
//	rectPrincipal.top = 0;
//
//	rectAppoint.width = 0;
//	rectAppoint.height = HAUTEUR_ECRAN;
//	rectAppoint.left = 0;
//	rectAppoint.top = 0;
//}
//
//void FondMobile::move(const int thrust)
//{
//	rectPrincipal.left += vitesse + thrust;
//
//	if (rectPrincipal.left > fondEcranT.getSize().x)
//	{
//		rectPrincipal.left -= fondEcranT.getSize().x;
//		rectPrincipal.width = LARGEUR_ECRAN;
//		rectAppoint.width = 0;
//	}
//
//	if ((rectPrincipal.left + rectPrincipal.width) > fondEcranT.getSize().x)
//	{
//		rectPrincipal.width = fondEcranT.getSize().x - rectPrincipal.left;
//		rectAppoint.width = LARGEUR_ECRAN - rectPrincipal.width;
//	}
//}
//
//void FondMobile::draw(RenderWindow* rw)
//{
//	fondEcran.setTextureRect(rectPrincipal);
//	fondEcran.setPosition(0, 0);
//	rw->draw(fondEcran);
//
//	if (rectAppoint.width > 0)
//	{
//		fondEcran.setTextureRect(rectAppoint);
//		fondEcran.setPosition(LARGEUR_ECRAN - (rectAppoint.width), 0);
//		rw->draw(fondEcran);
//	}
//}
